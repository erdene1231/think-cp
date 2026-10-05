-- Existing project: run this entire migration in Supabase SQL Editor.
-- Repeatable. Does not change existing progress or private-note access.
begin;

create table if not exists public.profiles (
  user_id uuid primary key references auth.users(id) on delete cascade,
  username text not null unique,
  constraint profiles_username_format check (username ~ '^[a-z0-9_]{3,24}$')
);
alter table public.profiles enable row level security;
revoke all on public.profiles from anon, authenticated;
grant select, insert, update on public.profiles to authenticated;

drop policy if exists "Read own profile" on public.profiles;
create policy "Read own profile" on public.profiles for select to authenticated
  using ((select auth.uid()) = user_id);
drop policy if exists "Insert own profile" on public.profiles;
create policy "Insert own profile" on public.profiles for insert to authenticated
  with check ((select auth.uid()) = user_id);
drop policy if exists "Update own profile" on public.profiles;
create policy "Update own profile" on public.profiles for update to authenticated
  using ((select auth.uid()) = user_id) with check ((select auth.uid()) = user_id);

create index if not exists progress_solved_problem_idx
  on public.progress(problem_id, user_id) where status = 'solved';

-- Narrow public projection: only usernames of users who marked this task solved.
-- SECURITY DEFINER is intentional: progress and profiles remain private under RLS.
create or replace function public.get_problem_solvers(
  p_problem_id text, p_offset integer default 0, p_limit integer default 50
)
returns table (username text, total_count bigint)
language sql stable security definer set search_path = ''
as $$
  select pr.username, count(*) over () as total_count
  from public.progress as pg
  join public.profiles as pr on pr.user_id = pg.user_id
  where pg.problem_id = p_problem_id and pg.status = 'solved'
  order by pr.username
  limit least(greatest(coalesce(p_limit, 50), 1), 50)
  offset greatest(coalesce(p_offset, 0), 0);
$$;
revoke all on function public.get_problem_solvers(text, integer, integer) from public;
grant execute on function public.get_problem_solvers(text, integer, integer) to anon, authenticated;

notify pgrst, 'reload schema';
commit;
