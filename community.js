export function normalizeUsername(value) {
  const username=String(value).trim().toLowerCase();
  if(!/^[a-z0-9_]{3,24}$/.test(username))throw new Error('Username нь 3–24 тэмдэгттэй, латин үсэг, тоо, _ ашигласан байна.');
  return username;
}
export function profileError(error) {
  if(error?.code==='23505')return 'Энэ username ашиглагдаж байна. Өөр нэр сонгоорой.';
  if(error?.code==='42P01'||error?.code==='PGRST205')return 'Username-ийн тохиргоо хараахан идэвхжээгүй байна. Багшдаа мэдэгдээрэй.';
  return error?.message || 'Username хадгалж чадсангүй. Дахин оролдоорой.';
}
export async function getProfile(client,userId) {
  const {data,error}=await client.from('profiles').select('username').eq('user_id',userId).maybeSingle();
  if(error)throw error;
  return data?.username || null;
}
export async function putProfile(client,userId,value) {
  const username=normalizeUsername(value);
  const {error}=await client.from('profiles').upsert({user_id:userId,username},{onConflict:'user_id'});
  if(error)throw error;
  return username;
}
export async function getSolvers(client,problemId,offset=0) {
  const {data,error}=await client.rpc('get_problem_solvers',{p_problem_id:problemId,p_offset:offset,p_limit:50});
  if(error)throw error;
  const rows=data || [];
  return {names:rows.map(row=>row.username),total:Number(rows[0]?.total_count || 0)};
}
