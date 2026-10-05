-- Run after 004-following-admin.sql. Repeatable, retains existing admins and tasks.
begin;
create table if not exists public.admin_grants (
 id bigint generated always as identity primary key,
 actor_id uuid references auth.users(id) on delete set null,
 target_id uuid references auth.users(id) on delete set null,
 created_at timestamptz not null default now()
);
alter table public.admin_grants enable row level security;
revoke all on public.admin_grants from public,anon,authenticated;
create or replace function public.admin_grant(p_user_id uuid) returns void
language plpgsql security definer set search_path='' as $$
begin
 if not public.is_admin() then raise exception 'Admin эрх шаардлагатай.' using errcode='42501'; end if;
 if p_user_id is null or not exists(select 1 from public.profiles where user_id=p_user_id) then raise exception 'Хэрэглэгч олдсонгүй.'; end if;
 insert into public.admin_accounts(user_id) values(p_user_id) on conflict do nothing;
 if found then insert into public.admin_grants(actor_id,target_id) values(auth.uid(),p_user_id); end if;
end;
$$;
create or replace function public.admin_list() returns table(user_id uuid,username text,full_name text,is_primary boolean)
language plpgsql stable security definer set search_path='' as $$
begin
 if not public.is_admin() then raise exception 'Admin эрх шаардлагатай.' using errcode='42501'; end if;
 return query select p.user_id,p.username,p.full_name,a.is_primary from public.admin_accounts a join public.profiles p on p.user_id=a.user_id order by a.is_primary desc,p.username;
end;
$$;
create or replace function public.admin_import_problems(p_problems jsonb) returns jsonb
language plpgsql security definer set search_path='' as $$
declare task_body jsonb; result jsonb:='[]'::jsonb; saved jsonb; idx integer:=0;
begin
 if not public.is_admin() then raise exception 'Admin эрх шаардлагатай.' using errcode='42501'; end if;
 if p_problems is null or jsonb_typeof(p_problems)<>'array' then raise exception 'Бодлогын жагсаалт оруулна уу.'; end if;
 if jsonb_array_length(p_problems) not between 1 and 100 or pg_column_size(p_problems)>2097152 then raise exception 'Нэг удаад 1–100 бодлого, 2 MB хүртэл байна.'; end if;
 -- Entire batch is one transaction. Concurrent imports cannot bypass duplicate checks.
 perform pg_catalog.pg_advisory_xact_lock(72483160);
 for task_body in select value from jsonb_array_elements(p_problems) loop
  idx:=idx+1;
  begin
   if exists(select 1 from public.problem_catalog p where p.body->>'url'=task_body->>'url' or (p.body->>'source'=task_body->>'source' and lower(btrim(p.body->>'ref'))=lower(btrim(task_body->>'ref')))) then
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
revoke all on function public.admin_grant(uuid),public.admin_list(),public.admin_import_problems(jsonb) from public,anon,authenticated;
grant execute on function public.admin_grant(uuid),public.admin_list(),public.admin_import_problems(jsonb) to authenticated;
commit;
