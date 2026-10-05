-- Run AFTER schema.sql and 002-usernames-solvers.sql. Repeatable.
begin;
alter table public.profiles alter column username drop not null;
alter table public.profiles add column if not exists full_name text not null default '' check (length(full_name)<=100);
alter table public.profiles add column if not exists school text not null default '' check (length(school)<=160);
alter table public.profiles add column if not exists avatar_path text check (avatar_path is null or (length(avatar_path)<=200 and avatar_path ~ ('^' || user_id::text || '/[a-zA-Z0-9_-]+\.(webp|png|jpg|jpeg)$')));

-- Register every account, including those without a username. Never copy email to profiles.
create or replace function public.create_account_profile()
returns trigger language plpgsql security definer set search_path = '' as $$
begin
 insert into public.profiles(user_id) values (new.id) on conflict(user_id) do nothing;
 return new;
end;
$$;
revoke all on function public.create_account_profile() from public, anon, authenticated;
drop trigger if exists think_cp_account_profile on auth.users;
create trigger think_cp_account_profile after insert on auth.users
 for each row execute function public.create_account_profile();
insert into public.profiles(user_id) select id from auth.users on conflict(user_id) do nothing;

-- Only catalogued tasks count toward the community ranking.
create table if not exists public.problem_catalog(problem_id text primary key);
revoke all on public.problem_catalog from public, anon, authenticated;
grant select on public.problem_catalog to anon, authenticated;
insert into public.problem_catalog(problem_id) values
 ('cf-1665B'),
 ('cf-1440B'),
 ('cf-1831B'),
 ('cf-1691B'),
 ('cf-1624C'),
 ('cf-1304B'),
 ('cf-1741C'),
 ('cf-1616B'),
 ('cf-1618C'),
 ('cf-1382B'),
 ('cf-1343C'),
 ('cf-1497B'),
 ('cf-1354B'),
 ('cf-1364A'),
 ('cf-1601A'),
 ('cf-1661B'),
 ('cf-1534C'),
 ('cf-1401C'),
 ('cf-1654C'),
 ('cf-1520E'),
 ('cf-1332B'),
 ('cf-1380C'),
 ('cf-1605C'),
 ('cf-1506D'),
 ('cf-1526B'),
 ('cf-1627C'),
 ('cf-1370C'),
 ('cf-1324D'),
 ('cf-1515C'),
 ('cf-1451C'),
 ('cf-1363B'),
 ('cf-1374D'),
 ('cf-1466D'),
 ('cf-1547E'),
 ('cf-1368B'),
 ('cf-1444A'),
 ('cf-1325C'),
 ('cf-1490F'),
 ('cf-1492C'),
 ('cf-1426D'),
 ('cf-1515D'),
 ('cf-1385D'),
 ('cf-1416A'),
 ('cf-1513C'),
 ('cf-1389B'),
 ('cf-1407C'),
 ('cf-1353D'),
 ('cf-1481C'),
 ('cf-1398C'),
 ('cf-1622C'),
 ('cf-1748C'),
 ('cf-1368D'),
 ('cf-1538D'),
 ('cf-1343D'),
 ('cf-1644D'),
 ('cf-1537D'),
 ('cf-1392D'),
 ('cf-1336B'),
 ('cf-1525D'),
 ('cf-1552D'),
 ('cf-1572A'),
 ('cf-1398D'),
 ('cf-1560E'),
 ('cf-1450D'),
 ('cf-1367D'),
 ('cf-1508A'),
 ('cf-1354D'),
 ('cf-1288D'),
 ('cf-1360H'),
 ('cf-1486D'),
 ('cf-1406D'),
 ('cf-1494D'),
 ('cf-1479C'),
 ('cses-1070'),
 ('cses-1755'),
 ('cses-2165'),
 ('cses-1092'),
 ('cses-1097'),
 ('cses-1072'),
 ('cses-1624'),
 ('cses-1141'),
 ('cses-2431'),
 ('cses-2217'),
 ('egoi-2023-inflation')
on conflict(problem_id) do nothing;

create or replace view public.community_summary as
select pr.user_id, pr.username, pr.full_name, pr.school, pr.avatar_path,
 count(pg.problem_id) filter(where pg.status='solved') as solved_count,
 count(pg.problem_id) filter(where pg.status='trying') as trying_count
from public.profiles pr
left join (public.progress pg inner join public.problem_catalog pc using(problem_id)) on pg.user_id=pr.user_id
group by pr.user_id;
revoke all on public.community_summary from public, anon, authenticated;

create or replace function public.get_leaderboard(p_offset integer default 0, p_limit integer default 50, p_search text default '')
returns table(user_id uuid,username text,full_name text,school text,avatar_path text,solved_count bigint,trying_count bigint,rank bigint,total_count bigint)
language sql stable security definer set search_path='' as $$
 with ranked as (select s.*,dense_rank() over(order by s.solved_count desc) as rank from public.community_summary s)
 select r.*, count(*) over() from ranked r
 where coalesce(r.username,'') ilike '%'||left(coalesce(p_search,''),100)||'%'
    or r.full_name ilike '%'||left(coalesce(p_search,''),100)||'%'
    or r.school ilike '%'||left(coalesce(p_search,''),100)||'%'
 order by r.solved_count desc,r.username nulls last,r.user_id
 limit least(greatest(coalesce(p_limit,50),1),50) offset greatest(coalesce(p_offset,0),0);
$$;
create or replace function public.get_public_profile(p_user_id uuid)
returns table(user_id uuid,username text,full_name text,school text,avatar_path text,solved_count bigint,trying_count bigint,rank bigint)
language sql stable security definer set search_path='' as $$
 select r.* from (select s.*,dense_rank() over(order by s.solved_count desc) as rank from public.community_summary s) r where r.user_id=p_user_id;
$$;
create or replace function public.get_public_progress(p_user_id uuid)
returns table(problem_id text,status text)
language sql stable security definer set search_path='' as $$
 select pg.problem_id,pg.status from public.progress pg join public.problem_catalog pc using(problem_id)
 where pg.user_id=p_user_id and pg.status in ('solved','trying') order by pg.problem_id;
$$;
-- Accounts without a username are on the leaderboard but not the named solver list.
create or replace function public.get_problem_solvers(p_problem_id text,p_offset integer default 0,p_limit integer default 50)
returns table(username text,total_count bigint)
language sql stable security definer set search_path='' as $$
 select pr.username,count(*) over() from public.progress pg join public.profiles pr on pr.user_id=pg.user_id
 where pg.problem_id=p_problem_id and pg.status='solved' and pr.username is not null
 order by pr.username limit least(greatest(coalesce(p_limit,50),1),50) offset greatest(coalesce(p_offset,0),0);
$$;
revoke all on function public.get_problem_solvers(text,integer,integer) from public;
grant execute on function public.get_problem_solvers(text,integer,integer) to anon,authenticated;

create or replace function public.get_profile_id(p_username text)
returns uuid language sql stable security definer set search_path='' as $$
 select pr.user_id from public.profiles pr where pr.username=lower(p_username);
$$;
revoke all on function public.get_leaderboard(integer,integer,text),public.get_public_profile(uuid),public.get_public_progress(uuid),public.get_profile_id(text) from public;
grant execute on function public.get_leaderboard(integer,integer,text),public.get_public_profile(uuid),public.get_public_progress(uuid),public.get_profile_id(text) to anon,authenticated;

create table if not exists public.friendships (
 user_low uuid not null references auth.users(id) on delete cascade,
 user_high uuid not null references auth.users(id) on delete cascade,
 requested_by uuid not null references auth.users(id) on delete cascade,
 status text not null default 'pending' check(status in ('pending','accepted')),
 created_at timestamptz not null default now(),
 primary key(user_low,user_high),
 check(user_low<user_high), check(requested_by in (user_low,user_high))
);
create index if not exists friendships_high_idx on public.friendships(user_high);
alter table public.friendships enable row level security;
revoke all on public.friendships from public,anon,authenticated;
grant select on public.friendships to authenticated;
drop policy if exists "Read involved friendships" on public.friendships;
create policy "Read involved friendships" on public.friendships for select to authenticated
 using ((select auth.uid()) in (user_low,user_high));

create or replace function public.get_friend_status(p_user_id uuid)
returns text language sql stable security definer set search_path='' as $$
 select case when auth.uid() is null then 'guest' when auth.uid()=p_user_id then 'self'
 when f.status='accepted' then 'friend' when f.requested_by=auth.uid() then 'outgoing'
 when f.status='pending' then 'incoming' else 'none' end
 from (select 1) dummy left join public.friendships f on f.user_low=least(auth.uid(),p_user_id) and f.user_high=greatest(auth.uid(),p_user_id);
$$;
create or replace function public.friend_action(p_user_id uuid,p_action text)
returns text language plpgsql security definer set search_path='' as $$
declare me uuid:=auth.uid(); lo uuid; hi uuid; f public.friendships%rowtype;
begin
 if me is null then raise exception 'Нэвтэрнэ үү.' using errcode='42501'; end if;
 if me=p_user_id or p_user_id is null then raise exception 'Өөр хэрэглэгч сонгоно уу.'; end if;
 if not exists(select 1 from public.profiles where user_id=p_user_id) then raise exception 'Хэрэглэгч олдсонгүй.'; end if;
 lo:=least(me,p_user_id);hi:=greatest(me,p_user_id);
 -- Serialize actions on a pair, including simultaneous opposite requests.
 perform pg_catalog.pg_advisory_xact_lock(pg_catalog.hashtextextended(lo::text||hi::text,0));
 select * into f from public.friendships where user_low=lo and user_high=hi for update;
 if p_action='request' then
  if f.user_low is not null then raise exception 'Хүсэлт эсвэл найзын холбоо аль хэдийн байна.'; end if;
  insert into public.friendships(user_low,user_high,requested_by) values(lo,hi,me);return 'outgoing';
 elsif p_action='accept' then
  if f.status is distinct from 'pending' or f.requested_by=me then raise exception 'Зөвшөөрөх хүсэлт олдсонгүй.'; end if;
  update public.friendships set status='accepted' where user_low=lo and user_high=hi;return 'friend';
 elsif p_action in ('decline','cancel','remove') then
  if f.user_low is null then raise exception 'Холбоо олдсонгүй.'; end if;
  if p_action='decline' and (f.status<>'pending' or f.requested_by=me) then raise exception 'Татгалзах хүсэлт олдсонгүй.'; end if;
  if p_action='cancel' and (f.status<>'pending' or f.requested_by<>me) then raise exception 'Цуцлах хүсэлт олдсонгүй.'; end if;
  if p_action='remove' and f.status<>'accepted' then raise exception 'Найзын холбоо олдсонгүй.'; end if;
  delete from public.friendships where user_low=lo and user_high=hi;return 'none';
 end if;
 raise exception 'Танихгүй үйлдэл.';
end;
$$;
create or replace function public.get_friends(p_kind text default 'friend',p_offset integer default 0,p_limit integer default 50)
returns table(user_id uuid,username text,full_name text,school text,avatar_path text,solved_count bigint,trying_count bigint,relationship text,total_count bigint)
language sql stable security definer set search_path='' as $$
 with involved as (
  select s.*,case when f.status='accepted' then 'friend' when f.requested_by=auth.uid() then 'outgoing' else 'incoming' end as relationship
  from public.friendships f join public.community_summary s on s.user_id=case when f.user_low=auth.uid() then f.user_high else f.user_low end
  where auth.uid() in (f.user_low,f.user_high)
 ) select i.*,count(*) over() from involved i where i.relationship=p_kind
 order by i.solved_count desc,i.username nulls last,i.user_id
 limit least(greatest(coalesce(p_limit,50),1),50) offset greatest(coalesce(p_offset,0),0);
$$;
revoke all on function public.get_friend_status(uuid),public.friend_action(uuid,text),public.get_friends(text,integer,integer) from public;
grant execute on function public.get_friend_status(uuid),public.friend_action(uuid,text),public.get_friends(text,integer,integer) to authenticated;

insert into storage.buckets(id,name,public,file_size_limit,allowed_mime_types)
values('think-cp-avatars','think-cp-avatars',true,2097152,array['image/png','image/jpeg','image/webp'])
on conflict(id) do update set public=excluded.public,file_size_limit=excluded.file_size_limit,allowed_mime_types=excluded.allowed_mime_types;
drop policy if exists "Think CP avatar upload" on storage.objects;
create policy "Think CP avatar upload" on storage.objects for insert to authenticated with check(
 bucket_id='think-cp-avatars' and (storage.foldername(name))[1]=(select auth.uid())::text
);
drop policy if exists "Think CP own avatar read" on storage.objects;
create policy "Think CP own avatar read" on storage.objects for select to authenticated using(
 bucket_id='think-cp-avatars' and (storage.foldername(name))[1]=(select auth.uid())::text
);
drop policy if exists "Think CP avatar delete" on storage.objects;
create policy "Think CP avatar delete" on storage.objects for delete to authenticated using(
 bucket_id='think-cp-avatars' and (storage.foldername(name))[1]=(select auth.uid())::text
);
notify pgrst,'reload schema';
commit;
