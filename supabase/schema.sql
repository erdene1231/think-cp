-- Run once in your Supabase project's SQL Editor.
create table if not exists public.progress (
  user_id uuid not null references auth.users(id) on delete cascade,
  problem_id text not null check (length(problem_id) between 1 and 100),
  status text not null default 'new' check (status in ('new','trying','solved')),
  hints integer not null default 0 check (hints between 0 and 3),
  notes text not null default '' check (length(notes) <= 5000),
  primary key (user_id, problem_id)
);
alter table public.progress enable row level security;
revoke all on public.progress from anon;
grant select, insert, update on public.progress to authenticated;
create policy "Read own progress" on public.progress for select to authenticated using ((select auth.uid()) = user_id);
create policy "Insert own progress" on public.progress for insert to authenticated with check ((select auth.uid()) = user_id);
create policy "Update own progress" on public.progress for update to authenticated using ((select auth.uid()) = user_id) with check ((select auth.uid()) = user_id);
