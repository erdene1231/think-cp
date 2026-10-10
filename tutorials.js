import {levels,levelNames,validateTutorial,view} from './tutorial-model.js?v=13';
import {setupTutorialEditor} from './tutorial-editor.js?v=13';
const $=id=>document.getElementById(id);
export const node=(tag,text,cls)=>{const el=document.createElement(tag);if(text!==undefined)el.textContent=text;if(cls)el.className=cls;return el;};
let mathPromise=null,mathQueue=Promise.resolve();
function mathjax(){
 if(window.MathJax?.typesetPromise)return Promise.resolve(window.MathJax);
 if(mathPromise)return mathPromise;
 mathPromise=new Promise((resolve,reject)=>{
  window.MathJax={loader:{paths:{mathjax:new URL('./vendor/mathjax',location.href).href},load:['ui/safe']},options:{safeOptions:{allow:{URLs:'none',classes:'none',cssIDs:'none',styles:'none'}}},tex:{packages:['base','ams','newcommand','noundefined','configmacros'],inlineMath:[['\\(','\\)'],['$','$']],displayMath:[['\\[','\\]'],['$$','$$']],processEscapes:true,maxBuffer:20000},svg:{fontCache:'local'},startup:{typeset:false}};
  const script=document.createElement('script');script.src='./vendor/mathjax/tex-svg.js';script.async=true;
  const timer=setTimeout(fail,15000);
  function fail(){clearTimeout(timer);script.remove();mathPromise=null;reject(new Error('MathJax ачаалсангүй / Could not load MathJax.'));}
  script.onerror=fail;script.onload=()=>{clearTimeout(timer);if(!window.MathJax?.startup?.promise)return fail();window.MathJax.startup.promise.then(()=>resolve(window.MathJax)).catch(fail);};document.head.append(script);
 });return mathPromise;
}
export function renderBlock(b,parent,lang='mn'){
 if(b.type==='p')parent.append(node('p',b.text));
 else if(b.type==='note'){const a=node('aside',undefined,'tutorial-note');a.append(node('p',b.text));parent.append(a);}
 else if(b.type==='math')parent.append(node('div','$$'+b.tex+'$$','tutorial-math'));
 else if(b.type==='list'||b.type==='ordered'){const list=node(b.type==='list'?'ul':'ol');for(const x of b.items)list.append(node('li',x));parent.append(list);}
 else if(b.type==='table'){const wrap=node('div',undefined,'tutorial-table-wrap'),table=node('table'),head=node('thead'),row=node('tr');for(const h of b.headers){const th=node('th',h);th.scope='col';row.append(th);}head.append(row);table.append(head);const body=node('tbody');for(const cells of b.rows){const tr=node('tr');for(const c of cells)tr.append(node('td',c));body.append(tr);}table.append(body);wrap.append(table);parent.append(wrap);}
 else if(b.type==='code'){const wrap=node('div',undefined,'tutorial-code'),bar=node('div',undefined,'code-toolbar'),pre=node('pre'),code=node('code',b.text,'language-cpp'),button=node('button',lang==='en'?'Copy code':'Код хуулах');button.type='button';button.onclick=()=>void copy(b.text,button,lang==='en'?'Copied':'Хуулагдлаа');bar.append(node('span','C++17'),button);pre.append(code);wrap.append(bar,pre);parent.append(wrap);try{window.hljs?.highlightElement(code);}catch{/* Plain code remains readable. */}}
 else if(b.type==='links'){const list=node('ul',undefined,'tutorial-reading-links');for(const x of b.items){let u;try{u=new URL(x.url);}catch{continue;}if(u.protocol!=='https:'||u.username||u.password)continue;const li=node('li'),a=node('a',x.label);a.href=u.href;a.target='_blank';a.rel='noopener noreferrer';li.append(a);list.append(li);}parent.append(list);}
}
export function drawArticle(t,parent,lang){const v=view(t,lang);parent.replaceChildren();for(const [i,s] of v.sections.entries()){const part=node('section');part.id='tutorial-'+t.id+'-'+i;part.append(node('h3',s.title));for(const b of s.blocks)renderBlock(b,part,lang);parent.append(part);}}
export function typeset(elements,build){
 mathQueue=mathQueue.catch(()=>{}).then(async()=>{window.MathJax?.typesetClear?.(elements);if(build&&build()===false)return;const mj=await mathjax();await mj.typesetPromise(elements);});return mathQueue;
}
async function copy(text,button,success){try{await navigator.clipboard.writeText(text);const previous=button.textContent;button.textContent=success;setTimeout(()=>button.textContent=previous,1800);}catch{$('tutorial-message').textContent='Хуулах боломжгүй байна / Copy unavailable.';}}
export function setupTutorials(ctx){
 let topics=[],current=null,renderTurn=0,resultTurn=0,loadTurn=0,lang='mn',onlineReady=false,editor;
 try{lang=localStorage.getItem('erdene:tutorial-language')==='en'?'en':'mn';}catch{}$('tutorial-language').value=lang;
 const tr=(mn,en)=>lang==='en'?en:mn;
 const categories={'Суурь':'Fundamentals','Array ба search':'Arrays & searching'};
 const categoryName=c=>lang==='en'?(categories[c]||c):c;
 const labels=()=>{for(const o of $('tutorial-category').options)o.textContent=o.value?categoryName(o.value):tr('Бүх бүлэг','All categories');document.documentElement.lang=location.hash.startsWith('#tutorial')?lang:'mn';$('tutorial-copy-link').textContent=tr('Холбоос хуулах','Copy link');$('tutorial-search').placeholder=tr('Binary search, dp, мод, хамгийн богино зам…','Binary search, dp, tree, shortest path…');document.querySelectorAll('.tutorial-back').forEach(a=>a.textContent=tr('← Бүх tutorials','← All tutorials'));};
 function accept(list){topics=list.map(row=>{const t=validateTutorial(row.body||row);return {...t,revision:row.revision||0,searchText:JSON.stringify(t).toLowerCase()};}).sort((a,b)=>levels.indexOf(a.levelKey)-levels.indexOf(b.levelKey)||a.order-b.order||a.id.localeCompare(b.id));
  const old=$('tutorial-category').value,all=node('option',tr('Бүх бүлэг','All categories'));all.value='';$('tutorial-category').replaceChildren(all);for(const c of new Set(topics.map(t=>t.category))){const o=node('option',categoryName(c));o.value=c;$('tutorial-category').append(o);}$('tutorial-category').value=[...$('tutorial-category').options].some(o=>o.value===old)?old:'';editor?.refresh();route();results();}
 function results(){
  const words=$('tutorial-search').value.trim().toLowerCase().split(/\s+/).filter(Boolean),category=$('tutorial-category').value,level=$('tutorial-level').value;
  const matches=topics.filter(t=>(!category||t.category===category)&&(!level||t.levelKey===level)&&words.every(w=>t.searchText.includes(w)));
  $('tutorial-count').textContent=matches.length+' / '+topics.length+tr(' хичээл',' tutorials');
  const snapshot=matches,selectedLang=lang,turn=++resultTurn;
  void typeset([$ ('tutorial-grid')],()=>{if(turn!==resultTurn)return false;const grid=$('tutorial-grid');grid.replaceChildren();for(const key of levels){const group=snapshot.filter(t=>t.levelKey===key);if(!group.length)continue;const title=node('h3',levelNames[selectedLang][levels.indexOf(key)],'tutorial-level-heading');grid.append(title);for(const t of group){const v=view(t,selectedLang),a=node('a',undefined,'tutorial-card');a.href='#tutorial/'+t.id;a.append(node('p',selectedLang==='en'?(categories[t.category]||t.category):t.category,'eyebrow'),node('h4',v.title),node('p',v.summary),node('small',selectedLang==='en'?'Example · Proof · C++17 · Exercises →':'Жишээ · Баталгаа · C++17 · Дасгал →'));grid.append(a);}}if(!snapshot.length)grid.append(node('p',selectedLang==='en'?'No matching tutorials. Try another keyword.':'Тохирох хичээл олдсонгүй. Өөр түлхүүр үгээр хайгаарай.','muted'));}).catch(()=>{});
 }
 function renderTopic(t,part){
  current=t;const turn=++renderTurn,selectedLang=lang,v=view(t,lang);labels();$('tutorial-browser').hidden=true;$('tutorial-reader').hidden=false;$('tutorial-level').closest('label').hidden=true;
  document.title=v.title+' — Erdene Club';$('tutorial-message').textContent='';$('tutorial-content').setAttribute('aria-busy','true');$('tutorial-math-message').textContent=tr('Томъёог дүрсэлж байна…','Rendering mathematics…');$('tutorial-math-retry').hidden=true;
  const elements=[$('tutorial-title'),$('tutorial-summary'),$('tutorial-prerequisites'),$('tutorial-content')];
  void typeset(elements,()=>{if(turn!==renderTurn)return false;$('tutorial-title').textContent=v.title;$('tutorial-summary').textContent=v.summary;$('tutorial-prerequisites').textContent=(selectedLang==='en'?'Prerequisites: ':'Урьдчилан мэдэх: ')+v.prerequisites;$('tutorial-meta').textContent=categoryName(t.category)+' · '+levelNames[selectedLang][levels.indexOf(t.levelKey)];drawArticle(t,$('tutorial-content'),selectedLang);$('tutorial-content').lang=selectedLang;$('tutorial-toc').replaceChildren(node('strong',selectedLang==='en'?'In this tutorial':'Энэ хичээлд'));v.sections.forEach((s,i)=>{const a=node('a',s.title);a.href='#tutorial/'+t.id+'/part/'+i;$('tutorial-toc').append(a);});$('tutorial-related').replaceChildren(node('h3',selectedLang==='en'?'Related topics':'Холбоотой сэдвүүд'));for(const id of t.related){const o=topics.find(x=>x.id===id);if(o){const a=node('a',view(o,selectedLang).title);a.href='#tutorial/'+id;$('tutorial-related').append(a);}}})
  .then(()=>{if(turn!==renderTurn)return false;$('tutorial-math-message').textContent='';const target=Number.isInteger(part)?$('tutorial-'+t.id+'-'+part):$('tutorial-title');target?.scrollIntoView({block:'start'});$('tutorial-title').focus({preventScroll:true});})
  .catch(e=>{if(turn===renderTurn){$('tutorial-math-message').textContent=e.message+tr(' Томъёог түр LaTeX хэлбэрээр харуулж байна.',' Showing raw LaTeX temporarily.');$('tutorial-math-retry').hidden=false;}}).finally(()=>{if(turn===renderTurn)$('tutorial-content').setAttribute('aria-busy','false');});
 }
 function route(){
  labels();if(!topics.length)return;const m=location.hash.match(/^#tutorial\/([a-z0-9-]+)(?:\/part\/(\d+))?$/);
  if(m){const t=topics.find(x=>x.id===m[1]);if(t){const part=m[2]===undefined?undefined:Number(m[2]);if(current?.id===t.id&&part!==undefined){$('tutorial-'+t.id+'-'+part)?.scrollIntoView({block:'start'});}else renderTopic(t,part);return;}$('tutorial-message').textContent=tr('Хичээл олдсонгүй. Жагсаалтаас сонгоно уу.','Tutorial not found. Choose from the list.');}
  ++renderTurn;current=null;if(location.hash==='#tutorials'||m){$('tutorial-browser').hidden=false;$('tutorial-reader').hidden=true;$('tutorial-level').closest('label').hidden=false;results();}
 }
 async function connected(){
  if(!ctx.client())return;const turn=++loadTurn;
  try{const {data,error}=await ctx.client().rpc('get_tutorials');if(error)throw error;if(turn!==loadTurn)return;if(!Array.isArray(data)||!data.length)throw new Error('Tutorial data missing');onlineReady=true;accept(data);}
  catch{if(turn===loadTurn){onlineReady=false;editor?.refresh();}}
  editor?.accountChanged(true);
 }
 $('tutorial-language').onchange=()=>{lang=$('tutorial-language').value;try{localStorage.setItem('erdene:tutorial-language',lang);}catch{}current=null;results();route();};$('tutorial-search').addEventListener('input',results);$('tutorial-category').onchange=results;$('tutorial-level').onchange=results;
 $('tutorial-copy-link').onclick=()=>void copy(location.href,$('tutorial-copy-link'),tr('Хуулагдлаа','Copied'));$('tutorial-math-retry').onclick=()=>{if(current)renderTopic(current);};window.addEventListener('hashchange',route);
 editor=setupTutorialEditor({...ctx,topics:()=>topics,ready:()=>onlineReady,reload:connected,saved(row){accept(topics.map(t=>t.id===row.body.id?row:{body:t,revision:t.revision}));}});
 void fetch('./tutorials.json?v=13').then(r=>{if(!r.ok)throw new Error();return r.json();}).then(data=>{if(!onlineReady)accept(data.tutorials);}).catch(()=>{$('tutorial-grid').textContent='Tutorials ачаалсангүй / Could not load tutorials.';});
 return {connected,accountChanged(){editor.accountChanged();}};
}
