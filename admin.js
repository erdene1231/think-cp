import {rpc,accountError} from './accounts.js?v=6';
import {validateProblem} from './problem-store.js?v=7';
export function setupAdmin(ctx) {
 const $=id=>document.getElementById(id);let rows=[],selected=null,admin=false,accountId=null,token=0,busy=false;
 function setBusy(value){busy=value;for(const el of $('admin-form').querySelectorAll('input,select,textarea,button'))el.disabled=value;$('admin-choose').disabled=value;$('admin-new').disabled=value;$('admin-reload').disabled=value;}
 function renderChoices(){const query=$('admin-search').value.trim().toLowerCase();$('admin-choose').replaceChildren();const option=(value,label)=>{const n=document.createElement('option');n.value=value;n.textContent=label;$('admin-choose').append(n);};option('','Шинэ бодлого нэмэх');
  for(const p of rows.filter(p=>(!p.archived||$('admin-show-archived').checked||p.number===selected?.number)&&([p.title,p.number,'#'+p.number,'#'+String(p.number).padStart(3,'0'),...p.tags].join(' ').toLowerCase().includes(query)||p.number===selected?.number)))option(String(p.number),'#'+p.number+' · '+p.title+(p.archived?' · Хассан':''));$('admin-choose').value=selected?String(selected.number):'';
 }
 function edit(p){selected=p;$('admin-form').reset();$('admin-title').value=p?.title||'';$('admin-source').value=p?.source||'Codeforces';$('admin-ref').value=p?.ref||'';$('admin-url').value=p?.url||'';$('admin-rating').value=p?.rating||1400;$('admin-rating-kind').value=p?.ratingKind||'official';$('admin-level').value=p?.level||'Practice';$('admin-priority').checked=!!p?.priority;$('admin-tags').value=p?.tags?.join(', ')||'';$('admin-lesson').value=p?.lesson||'';$('admin-editorial').value=p?.editorialUrl||'';
  for(let i=0;i<3;i++){ $('admin-hint-mn-'+i).value=p?.hints?.[i]||'';$('admin-hint-en-'+i).value=p?.hintsEn?.[i]||'';}
  $('admin-problem-id').textContent=p?'Бодлогын ID: #'+p.number+' · '+(p.archived?'Хассан':'Идэвхтэй'):'Шинэ бодлогын ID хадгалах үед автоматаар олгогдоно.';
  $('admin-archive').hidden=!p;$('admin-archive').textContent=p?.archived?'Бодлогыг сэргээх':'Бодлогыг хасах';$('admin-save').textContent=p?'Өөрчлөлт хадгалах':'Бодлого нэмэх';renderChoices();
 }
 async function load(){if(!admin||busy)return;const request=++token,uid=ctx.user()?.id;$('admin-message').textContent='Бодлогуудыг ачаалж байна…';
  try{const list=await rpc(ctx.client(),'get_admin_catalog');if(request!==token||uid!==ctx.user()?.id)return;rows=list||[];selected=selected?rows.find(p=>p.number===selected.number)||null:null;edit(selected);$('admin-message').textContent=rows.length+' бодлого · Хассан бодлогыг сэргээж болно.';}
  catch(e){if(request===token)$('admin-message').textContent=accountError(e);}
 }
 async function checkRole(){const request=++token,uid=ctx.user()?.id;admin=false;rows=[];selected=null;$('admin-section').hidden=true;$('admin-nav').hidden=true;if(!uid||!ctx.client())return;
  try{const allowed=await rpc(ctx.client(),'is_admin');if(request!==token||uid!==ctx.user()?.id)return;admin=allowed===true;$('admin-nav').hidden=!admin;$('admin-section').hidden=!admin;if(admin){edit(null);void load();}}
  catch{ /* No client-side email or metadata fallback can grant admin rights. */ }
 }
 function input(){return validateProblem({title:$('admin-title').value,source:$('admin-source').value,ref:$('admin-ref').value,url:$('admin-url').value.trim(),rating:$('admin-rating').value,ratingKind:$('admin-rating-kind').value,level:$('admin-level').value,priority:$('admin-priority').checked,tags:$('admin-tags').value.split(','),hints:Array.from({length:3},(_,i)=>$('admin-hint-mn-'+i).value.trim()),hintsEn:Array.from({length:3},(_,i)=>$('admin-hint-en-'+i).value.trim()),lesson:$('admin-lesson').value,editorialUrl:$('admin-editorial').value.trim()});}
 $('admin-form').onsubmit=async event=>{event.preventDefault();if(!admin||busy||!$('admin-form').reportValidity())return;const uid=ctx.user()?.id;let payload;try{payload=input();}catch(e){$('admin-message').textContent=e.message;return;}setBusy(true);$('admin-message').textContent='Хадгалж байна…';
  try{const saved=await rpc(ctx.client(),'admin_save_problem',{p_body:payload,p_number:selected?.number||null,p_revision:selected?.revision||null});if(uid!==ctx.user()?.id)return;selected=saved;await ctx.refreshCatalog();setBusy(false);await load();$('admin-message').textContent='#'+saved.number+' хадгалагдлаа.';}
  catch(e){if(uid===ctx.user()?.id)$('admin-message').textContent=accountError(e);}finally{setBusy(false);}
 };
 $('admin-archive').onclick=async()=>{if(!selected||!admin||busy)return;const p=selected,wasArchived=p.archived,uid=ctx.user()?.id;if(!wasArchived&&!window.confirm('#'+p.number+' · '+p.title+' бодлогыг жагсаалтаас хасах уу? Сэргээж болно; progress хадгалагдана.'))return;setBusy(true);
  try{await rpc(ctx.client(),'admin_archive_problem',{p_number:p.number,p_revision:p.revision,p_archived:!wasArchived});if(uid!==ctx.user()?.id)return;await ctx.refreshCatalog();setBusy(false);await load();$('admin-message').textContent=wasArchived?'Бодлого сэргээгдлээ.':'Бодлогыг жагсаалтаас хаслаа. Progress хадгалагдсан.';}
  catch(e){if(uid===ctx.user()?.id)$('admin-message').textContent=accountError(e);}finally{setBusy(false);}
 };
 $('admin-choose').onchange=()=>{edit(rows.find(p=>p.number===Number($('admin-choose').value))||null);$('admin-message').textContent='';};$('admin-new').onclick=()=>{edit(null);$('admin-message').textContent='';};$('admin-reload').onclick=()=>void load();$('admin-search').addEventListener('input',renderChoices);$('admin-show-archived').onchange=renderChoices;
 $('admin-source').onchange=()=>{if($('admin-source').value!=='Codeforces')$('admin-rating-kind').value='estimated';};
 return {accountChanged(){const id=ctx.user()?.id||null;if(id===accountId)return;accountId=id;token++;setBusy(false);$('admin-form').reset();void checkRole();},connected(){void checkRole();}};
}
