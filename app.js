import {EMPTY, cleanEntry, parseBackup} from './progress.js';
const $ = id => document.getElementById(id);
const STATUS = {new:'Эхлээгүй',trying:'Оролдож байгаа',solved:'Бодсон'};
let data, selectedPack='', selectedProblem, state={}, dirty={}, user=null, client=null, loading=false, syncing=false, syncAgain=false, epoch=0;
const cfg=window.THINK_CP_CONFIG || {};
const configured=Boolean(cfg.supabaseUrl && cfg.supabaseKey);
const key=()=> 'think-cp:v1:'+(user?.id || 'guest');
function notice(message) { $('notice').textContent=message; }
function readLocal() {
  try { const saved=JSON.parse(localStorage.getItem(key()) || '{}'); state={}; dirty={}; for(const [id,entry] of Object.entries(saved.progress || {})) if(data.problems.some(p=>p.id===id)) state[id]=cleanEntry(entry); for(const id of saved.dirty || []) if(state[id]) dirty[id]=state[id]; }
  catch {state={};dirty={};notice('Өмнөх хадгалалтыг уншиж чадсангүй. Progress татах боломжийг ашиглаарай.');}
}
function persist() {
  try {localStorage.setItem(key(),JSON.stringify({progress:state,dirty:Object.keys(dirty)}));return true;}
  catch {notice('Browser хадгалалт боломжгүй байна. Хуудсаа хаахаас өмнө progress-оо татаж аваарай.');return false;}
}
function entry(id) {return state[id] || {...EMPTY};}
function setEntry(id, patch) {if(loading)return; state[id]=cleanEntry({...entry(id),...patch});dirty[id]=state[id];const saved=persist();render();if(user)void sync();else if(saved)notice('Progress энэ browser-т хадгалагдлаа.');}
function el(tag, cls, text) {const node=document.createElement(tag); if(cls)node.className=cls;if(text!==undefined)node.textContent=text;return node;}
function render() {
  const solved=data.problems.filter(p=>entry(p.id).status==='solved').length;
  const trying=data.problems.filter(p=>entry(p.id).status==='trying').length;
  const percent=Math.round(solved/data.problems.length*100);
  $('total').textContent=data.problems.length;$('solved').textContent=solved;$('trying').textContent=trying;$('percent').textContent=percent+'%';$('progress').value=percent;
  const query=$('search').value.trim().toLowerCase(), source=$('source').value, status=$('status-filter').value;
  $('packs').replaceChildren();
  for(const pack of [{id:'',title:'Бүгд'},...data.packs]) {
    const b=el('button',pack.id===selectedPack?'active':'',pack.title);b.setAttribute('aria-pressed',String(pack.id===selectedPack));b.onclick=()=>{selectedPack=pack.id;render();};$('packs').append(b);
  }
  $('pack-note').textContent=data.packs.find(p=>p.id===selectedPack)?.description || 'Эхлээд “Халаалт”, дараа нь “Өөр өнцөг” багцыг туршаарай. Сэдвүүд бодсоны дараа нээгдэнэ.';
  $('problems').replaceChildren();
  const filtered=data.problems.filter(p=>(!selectedPack||p.pack===selectedPack)&&(!source||p.source===source)&&(!query||(p.title+' '+p.id+' '+p.ref).toLowerCase().includes(query))&&(!status||(status==='hinted'?entry(p.id).hints>0:entry(p.id).status===status)));
  for(const p of filtered) {
    const row=el('article','problem'), n=el('span','number',String(data.problems.indexOf(p)+1).padStart(2,'0')), b=el('button','open');b.disabled=loading;
    b.append(el('h3','',p.title),el('small','',p.source+' · '+p.ref+' · '+p.level));b.onclick=()=>openProblem(p);
    const badge=el('span','badge '+entry(p.id).status,STATUS[entry(p.id).status]);
    const arrow=el('button','arrow','↗');arrow.setAttribute('aria-label',p.title+' нээх');arrow.disabled=loading;arrow.onclick=()=>openProblem(p);
    if(entry(p.id).hints) b.append(el('span','hint-used','Hint '+entry(p.id).hints+'/3'));
    row.append(n,b,badge,arrow);$('problems').append(row);
  }
  if(!filtered.length)$('problems').append(el('p','muted','Тохирох бодлого олдсонгүй. Шүүлтүүрээ өөрчлөөрэй.'));
}
function openProblem(p) {selectedProblem=p;$('detail-title').textContent=p.title;$('detail-source').textContent=p.source+' · '+p.ref;$('detail-note').textContent=p.level;$('problem-link').href=p.url;$('notes').value=entry(p.id).notes;$('detail-feedback').textContent='';renderDetail();$('detail').showModal();}
function renderDetail() {
  if(!selectedProblem)return;const p=selectedProblem,e=entry(p.id);$('problem-status').value=e.status;$('hint-list').replaceChildren();
  p.hints.slice(0,e.hints).forEach((hint,i)=>{const h=el('div','hint');h.append(el('b','','HINT '+(i+1)),el('span','',hint));$('hint-list').append(h);});
  $('next-hint').hidden=e.hints===3;$('next-hint').textContent='Hint '+(e.hints+1)+' нээх';$('reflection').hidden=e.status!=='solved';$('tags').textContent='Сэдэв: '+p.tags.join(' · ');$('lesson').textContent=p.lesson;
}
async function switchUser(next) {
  if(user?.id===next?.id)return;
  const turn=++epoch;user=next;loading=!!user;$('detail').close();readLocal();render();updateAccount();
  if(user) {
    try {
      const {data:rows,error}=await client.from('progress').select('problem_id,status,hints,notes').eq('user_id',user.id);
      if(error)throw error;if(turn!==epoch)return;
      const remote={};for(const row of rows)if(data.problems.some(p=>p.id===row.problem_id))remote[row.problem_id]=cleanEntry(row);
      state={...remote,...dirty};persist();notice('Account-ын progress ачаалагдлаа.');
    } catch(error) {if(turn===epoch)notice('Онлайн progress ачаалагдсангүй. Энэ төхөөрөмжийн хуулбарыг ашиглаж байна: '+error.message);}
    finally {if(turn===epoch){loading=false;render();void sync();}}
  } else {notice('Зочин горим. Progress энэ browser-т хадгалагдана.');}
}
async function sync() {
  if(!user || !client || loading)return;
  if(syncing){syncAgain=true;return;}if(!Object.keys(dirty).length)return;
  syncing=true;const turn=epoch,uid=user.id, batch={...dirty};notice('Онлайнаар хадгалж байна…');
  try {
    const {error}=await client.from('progress').upsert(Object.entries(batch).map(([problem_id,e])=>({user_id:uid,problem_id,...e})),{onConflict:'user_id,problem_id'});
    if(error)throw error;if(turn!==epoch)return;
    for(const id of Object.keys(batch))if(dirty[id]===batch[id])delete dirty[id];persist();notice(Object.keys(dirty).length?'Өөрчлөлтийг хадгалж байна…':'Онлайн progress хадгалагдлаа.');
  } catch(error) {if(turn===epoch)notice('Онлайн хадгалалт амжилтгүй. Browser-т хадгалсан; дахин оролдох боломжтой. '+error.message);}
  finally {syncing=false;updateAccount();if(syncAgain){syncAgain=false;void sync();}}
}
function updateAccount() {
  $('account').textContent=user?'Миний account':'Нэвтрэх';$('storage-label').textContent=user?'Account + энэ browser':'Энэ browser-т хадгална';
  $('auth-form').hidden=!client||!!user;$('signout').hidden=!user;$('retry-sync').hidden=!user||!Object.keys(dirty).length;
  $('auth-info').textContent=user?'Нэвтэрсэн: '+user.email:client?'Email-аар бүртгүүлж, бусад төхөөрөмжөөс progress-оо үргэлжлүүлээрэй. Зочин progress автоматаар account руу шилжихгүй; татаж аваад нэвтэрсний дараа сэргээж болно.':'Account хараахан идэвхжээгүй. Одоогоор зочин горимоор ашиглаж, progress-оо энэ browser-т хадгалах эсвэл файл болгож татах боломжтой.';
}
async function authAction(signup) {
  if(!$('auth-form').reportValidity())return;const buttons=$('auth-form').querySelectorAll('button');buttons.forEach(b=>b.disabled=true);$('auth-feedback').textContent='Түр хүлээнэ үү…';
  try {
    const credentials={email:$('email').value.trim(),password:$('password').value};
    const result=signup?await client.auth.signUp({...credentials,options:{emailRedirectTo:location.origin+location.pathname}}):await client.auth.signInWithPassword(credentials);
    if(result.error)throw result.error;$('password').value='';$('auth-feedback').textContent=result.data.session?'Амжилттай нэвтэрлээ.':'Email баталгаажуулах холбоосоо шалгаад нэвтэрнэ үү.';await switchUser(result.data.session?.user || null);
  } catch(error){$('auth-feedback').textContent=error.message;}finally{buttons.forEach(b=>b.disabled=false);}
}
async function init() {
  const response=await fetch('./problems.json');if(!response.ok)throw new Error('Бодлогын санг ачаалж чадсангүй.');data=await response.json();readLocal();render();updateAccount();
  for(const id of ['search','source','status-filter'])$(id).addEventListener('input',render);
  document.querySelectorAll('[data-close]').forEach(b=>b.onclick=()=>$(b.dataset.close).close());
  $('account').onclick=()=>{updateAccount();$('auth').showModal();};
  $('problem-status').onchange=()=>{setEntry(selectedProblem.id,{status:$('problem-status').value});renderDetail();};
  $('next-hint').onclick=()=>{const e=entry(selectedProblem.id);setEntry(selectedProblem.id,{hints:Math.min(e.hints+1,3),status:e.status==='new'?'trying':e.status});renderDetail();};
  $('save-note').onclick=()=>{setEntry(selectedProblem.id,{notes:$('notes').value});$('detail-feedback').textContent='Тэмдэглэлийг progress-д нэмлээ. Хадгалалтын төлөвийг үндсэн хуудаснаас харна уу.';};
  $('export').onclick=()=>{const blob=new Blob([JSON.stringify({version:1,progress:state},null,2)],{type:'application/json'}),url=URL.createObjectURL(blob),a=el('a');a.href=url;a.download='think-cp-progress.json';a.click();setTimeout(()=>URL.revokeObjectURL(url),1000);};
  $('import').onchange=async event=>{
    const file=event.target.files[0],turn=epoch;if(!file)return;
    try {if(loading)throw new Error('Account ачаалагдаж байна. Түр хүлээгээд дахин сонгоно уу.');if(file.size>2_000_000)throw new Error('Файл хэт том байна.');const imported=parseBackup(JSON.parse(await file.text()),new Set(data.problems.map(p=>p.id)));if(turn!==epoch)throw new Error('Account солигдлоо. Файлаа дахин сонгоно уу.');if(!confirm('Файлд байгаа бодлогуудын progress-ийг сэргээх үү? Одоогийн ижил бодлогын төлөв солигдоно.'))return;for(const [id,e] of Object.entries(imported)){state[id]=e;dirty[id]=e;}const saved=persist();render();if(saved)notice('Progress сэргээгдлээ.');void sync();}
    catch(error){notice(error.message);}finally{event.target.value='';}
  };
  $('auth-form').onsubmit=event=>{event.preventDefault();void authAction(false);};$('signup').onclick=()=>void authAction(true);
  $('signout').onclick=async()=>{if(syncing){$('auth-feedback').textContent='Хадгалалт дуусахыг хүлээгээрэй.';return;}const {error}=await client.auth.signOut();if(error){$('auth-feedback').textContent=error.message;return;}await switchUser(null);$('auth-feedback').textContent='Account-аас гарлаа.';};
  $('retry-sync').onclick=()=>void sync();window.addEventListener('online',()=>void sync());
  if(configured) {
    try {
      const {createClient}=await import('https://cdn.jsdelivr.net/npm/@supabase/supabase-js@2/+esm');client=createClient(cfg.supabaseUrl,cfg.supabaseKey);
      const {data:sessionData,error}=await client.auth.getSession();if(error)throw error;await switchUser(sessionData.session?.user || null);
      client.auth.onAuthStateChange((_event,session)=>{setTimeout(()=>void switchUser(session?.user || null),0);});updateAccount();
    } catch(error){client=null;updateAccount();notice('Account холболт ажилласангүй: '+error.message);}
  }
}
init().catch(error=>{$('problems').textContent=error.message;notice('Хуудсаа дахин ачаалаарай.');});
