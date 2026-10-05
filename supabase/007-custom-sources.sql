-- Run after 006-optional-hints.sql. Persistent source options and JSON auto-registration.
begin;
create table if not exists public.problem_sources (
 name text primary key check(length(name) between 1 and 80),
 created_at timestamptz not null default now()
);
create unique index if not exists problem_sources_name_case_insensitive on public.problem_sources(lower(name));
alter table public.problem_sources enable row level security;
revoke all on public.problem_sources from public,anon,authenticated;
insert into public.problem_sources(name) values ('Codeforces'),('CSES'),('EGOI'),('Other') on conflict do nothing;
insert into public.problem_sources(name)
 select distinct on (lower(body->>'source')) body->>'source'
 from public.problem_catalog where body is not null and nullif(btrim(body->>'source'),'') is not null
 order by lower(body->>'source'),number
 on conflict do nothing;

create or replace function public.normalize_problem_source(p_name text) returns text
language plpgsql immutable set search_path='' as $$
declare name text;
begin
 name:=regexp_replace(btrim(p_name),'[[:space:]]+',' ','g');
 if name is null or name='' or length(name)>80 or p_name ~ '[[:cntrl:]]' then raise exception 'Source нэр 1–80 тэмдэгт байна.'; end if;
 return name;
end;
$$;
revoke all on function public.normalize_problem_source(text) from public,anon,authenticated;

create or replace function public.admin_add_source(p_name text) returns text
language plpgsql security definer set search_path='' as $$
declare saved text;
begin
 if not public.is_admin() then raise exception 'Admin эрх шаардлагатай.' using errcode='42501'; end if;
 insert into public.problem_sources as s(name) values(public.normalize_problem_source(p_name))
 on conflict(lower(name)) do update set name=s.name returning name into saved;
 return saved;
end;
$$;
revoke all on function public.admin_add_source(text) from public,anon;
grant execute on function public.admin_add_source(text) to authenticated;

create or replace function public.get_catalog() returns jsonb
language sql stable security definer set search_path='' as $$
 select jsonb_build_object(
 'problems',coalesce((select jsonb_agg(pc.body||jsonb_build_object('id',pc.problem_id,'number',pc.number,'revision',pc.revision) order by pc.number) from public.problem_catalog pc where not pc.archived and pc.body is not null),'[]'::jsonb),
 'knownIds',coalesce((select jsonb_agg(problem_id) from public.problem_catalog),'[]'::jsonb),
 'sources',coalesce((select jsonb_agg(name order by lower(name)) from public.problem_sources),'[]'::jsonb));
$$;
revoke all on function public.get_catalog() from public;
grant execute on function public.get_catalog() to anon,authenticated;
create or replace function public.admin_save_problem(p_body jsonb,p_number bigint default null,p_revision integer default null) returns jsonb
language plpgsql security definer set search_path='' as $$
declare current_row public.problem_catalog%rowtype; n bigint; task_id text; payload jsonb; pack text; rate integer; tag jsonb; hints jsonb; h jsonb;
begin
 if not public.is_admin() then raise exception 'Admin эрх шаардлагатай.' using errcode='42501'; end if;
 if p_body is null or jsonb_typeof(p_body)<>'object' or pg_column_size(p_body)>65536 then raise exception 'Бодлогын өгөгдөл буруу эсвэл хэт том байна.'; end if;
 if nullif(btrim(p_body->>'title'),'') is null or length(p_body->>'title')>200 then raise exception 'Бодлогын нэр 1–200 тэмдэгт байна.'; end if;
 if jsonb_typeof(p_body->'source') is distinct from 'string' then raise exception 'Source нэр оруулна уу.'; end if;
 p_body:=jsonb_set(p_body,'{source}',to_jsonb(public.normalize_problem_source(p_body->>'source')));
 if lower(p_body->>'source')='codeforces' then p_body:=jsonb_set(p_body,'{source}','"Codeforces"'::jsonb); end if;
 if nullif(btrim(p_body->>'ref'),'') is null or length(p_body->>'ref')>80 then raise exception 'Эх бодлогын ID оруулна уу.'; end if;
 if not public.valid_task_url(p_body->>'url') then raise exception 'HTTPS бодлогын холбоос оруулна уу.'; end if;
 if coalesce(p_body->>'editorialUrl','')<>'' and not public.valid_task_url(p_body->>'editorialUrl') then raise exception 'Editorial HTTPS холбоос байх ёстой.'; end if;
 if coalesce(p_body->>'rating','') !~ '^[0-9]{3,4}$' then raise exception 'Rating бүхэл тоо байна.'; end if;
 rate:=(p_body->>'rating')::integer;
 if rate not between 800 and 4000 then raise exception 'Rating 800–4000 хүрээнд байна.'; end if;
 if coalesce(p_body->>'ratingKind','') not in ('official','estimated') or (p_body->>'ratingKind'='official' and p_body->>'source'<>'Codeforces') then raise exception 'Rating-ийн төрлийг зөв сонгоно уу.'; end if;
 if jsonb_typeof(p_body->'priority') is distinct from 'boolean' then raise exception 'Priority сонголт буруу байна.'; end if;
 if coalesce(p_body->>'level','Practice') not in ('Practice','Interactive') then raise exception 'Төрөл сонгоно уу.'; end if;
 if jsonb_typeof(p_body->'tags') is distinct from 'array' then raise exception 'Tags жагсаалт оруулна уу.'; end if;
 if jsonb_array_length(p_body->'tags') not between 1 and 20 then raise exception '1–20 tag оруулна уу.'; end if;
 for tag in select value from jsonb_array_elements(p_body->'tags') loop
  if jsonb_typeof(tag)<>'string' or (tag#>>'{}') !~ '^[a-zA-Z0-9 +/&()_-]{1,50}$' then raise exception 'Tag бүр English, 1–50 тэмдэгт байна.'; end if;
 end loop;
 for hints in select coalesce(p_body->'hints','[]'::jsonb) union all select coalesce(p_body->'hintsEn','[]'::jsonb) loop
  if jsonb_typeof(hints) is distinct from 'array' then raise exception 'Хэл тус бүрд 3 hint оруулна уу.'; end if;
  if jsonb_array_length(hints) not in (0,3) then raise exception 'Hint-гүй эсвэл хэл тус бүрд 3 hint байна.'; end if;
  for h in select value from jsonb_array_elements(hints) loop
   if jsonb_typeof(h)<>'string' or nullif(btrim(h#>>'{}'),'') is null or length(h#>>'{}')>3000 then raise exception 'Hint бүр 1–3000 тэмдэгт байна.'; end if;
  end loop;
 end loop;
 if jsonb_array_length(coalesce(p_body->'hints','[]'::jsonb))<>jsonb_array_length(coalesce(p_body->'hintsEn','[]'::jsonb)) then raise exception 'Монгол болон English hint-ийн тоо ижил байна.'; end if;
 if length(coalesce(p_body->>'lesson',''))>2000 then raise exception 'Тайлбар 2000 тэмдэгт хүртэл байна.'; end if;
 -- Same lock order as atomic batch imports; register sources only after validation.
 perform pg_catalog.pg_advisory_xact_lock(72483160);
 p_body:=jsonb_set(p_body,'{source}',to_jsonb(public.admin_add_source(p_body->>'source')));
 pack:=case when p_body->>'source'='CSES' then 'cses' when p_body->>'source'='EGOI' then 'egoi' when rate<=1100 then 'foundation' when rate<=1500 then 'core' when rate<=1800 then 'challenge' when rate<=2100 then 'stretch' else 'advanced' end;
 if p_number is null then
  -- One creation at a time; numbers are permanent and never recycled.
  perform pg_catalog.pg_advisory_xact_lock(72483160);
  n:=pg_catalog.nextval('public.problem_number_seq');task_id:='task-'||n::text;
 else
  select * into current_row from public.problem_catalog where number=p_number for update;
  if current_row.problem_id is null then raise exception 'Бодлого олдсонгүй.'; end if;
  if current_row.revision is distinct from p_revision then raise exception 'Бодлого өөрчлөгдсөн байна. Дахин ачаалж засна уу.' using errcode='40001'; end if;
  n:=current_row.number;task_id:=current_row.problem_id;
 end if;
 payload:=jsonb_build_object('id',task_id,'number',n,'pack',pack,'title',btrim(p_body->>'title'),'source',p_body->>'source','ref',btrim(p_body->>'ref'),'url',p_body->>'url','rating',rate,'ratingKind',p_body->>'ratingKind','priority',(p_body->>'priority')::boolean,'level',coalesce(p_body->>'level','Practice'),'tags',p_body->'tags','hints',coalesce(p_body->'hints','[]'::jsonb),'hintsEn',coalesce(p_body->'hintsEn','[]'::jsonb),'lesson',coalesce(p_body->>'lesson',''));
 if coalesce(p_body->>'editorialUrl','')<>'' then payload:=payload||jsonb_build_object('editorialUrl',p_body->>'editorialUrl'); end if;
 if p_number is null then
  insert into public.problem_catalog(problem_id,number,body) values(task_id,n,payload);
 else
  update public.problem_catalog set body=payload,revision=revision+1,updated_at=now() where problem_id=task_id;
 end if;
 insert into public.problem_changes(problem_id,actor_id,action,previous_body,next_body) values(task_id,auth.uid(),case when p_number is null then 'create' else 'edit' end,current_row.body,payload);
 return payload||jsonb_build_object('revision',coalesce(current_row.revision,0)+1,'archived',coalesce(current_row.archived,false));
end;
$$;
revoke all on function public.admin_save_problem(jsonb,bigint,integer) from public,anon;
grant execute on function public.admin_save_problem(jsonb,bigint,integer) to authenticated;
create or replace function public.admin_import_problems(p_problems jsonb) returns jsonb
language plpgsql security definer set search_path='' as $$
declare task_body jsonb; result jsonb:='[]'::jsonb; saved jsonb; idx integer:=0;
begin
 if not public.is_admin() then raise exception 'Admin эрх шаардлагатай.' using errcode='42501'; end if;
 if p_problems is null or jsonb_typeof(p_problems)<>'array' then raise exception 'Бодлогын жагсаалт оруулна уу.'; end if;
 if jsonb_array_length(p_problems) not between 1 and 200 or pg_column_size(p_problems)>2097152 then raise exception 'Нэг удаад 1–200 бодлого, 2 MB хүртэл байна.'; end if;
 -- Entire batch is one transaction. Concurrent imports cannot bypass duplicate checks.
 perform pg_catalog.pg_advisory_xact_lock(72483160);
 for task_body in select value from jsonb_array_elements(p_problems) loop
  idx:=idx+1;
  begin
   if exists(select 1 from public.problem_catalog p where p.body->>'url'=task_body->>'url' or (lower(p.body->>'source')=lower(public.normalize_problem_source(task_body->>'source')) and lower(btrim(p.body->>'ref'))=lower(btrim(task_body->>'ref')))) then
    raise exception 'Энэ бодлого санд байна (хассан бодлого ч багтана).';
   end if;
   saved:=public.admin_save_problem(task_body);
   result:=result||jsonb_build_array(saved);
  exception when others then raise exception 'Бодлого %: %',idx,sqlerrm;
  end;
 end loop;
 return result;
end;
$$;
revoke all on function public.admin_import_problems(jsonb) from public,anon;
grant execute on function public.admin_import_problems(jsonb) to authenticated;
commit;
