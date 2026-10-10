const $=id=>document.getElementById(id);
const node=(tag,text,cls)=>{const el=document.createElement(tag);if(text!==undefined)el.textContent=text;if(cls)el.className=cls;return el;};
let topics=[],current=null,renderTurn=0,mathPromise=null,mathQueue=Promise.resolve();
const defaultTitle=document.title;
function mathjax(){
 if(window.MathJax?.typesetPromise)return Promise.resolve(window.MathJax);
 if(mathPromise)return mathPromise;
 mathPromise=new Promise((resolve,reject)=>{
  window.MathJax={tex:{inlineMath:[['\\(','\\)'],['$','$']],displayMath:[['\\[','\\]'],['$$','$$']]},svg:{fontCache:'local'},startup:{typeset:false}};
  const script=document.createElement('script');script.src='https://cdn.jsdelivr.net/npm/mathjax@3.2.2/es5/tex-svg.js';script.async=true;
  const timer=setTimeout(()=>fail(),15000);
  function fail(){clearTimeout(timer);script.remove();mathPromise=null;reject(new Error('Томъёоны renderer ачаалсангүй. Интернэтээ шалгаад дахин оролдоорой.'));}
  script.onerror=fail;
  script.onload=()=>{clearTimeout(timer);if(!window.MathJax?.startup?.promise)return fail();window.MathJax.startup.promise.then(()=>resolve(window.MathJax)).catch(fail);};
  document.head.append(script);
 });
 return mathPromise;
}
function renderBlock(block,parent){
 if(block.type==='p')parent.append(node('p',block.text));
 else if(block.type==='note'){const aside=node('aside',undefined,'tutorial-note');aside.append(node('p',block.text));parent.append(aside);}
 else if(block.type==='math')parent.append(node('div','\\['+block.tex+'\\]','tutorial-math'));
 else if(block.type==='list'||block.type==='ordered'){const list=node(block.type==='list'?'ul':'ol');for(const item of block.items)list.append(node('li',item));parent.append(list);}
 else if(block.type==='table'){const wrap=node('div',undefined,'tutorial-table-wrap'),table=node('table'),head=node('thead'),row=node('tr');for(const title of block.headers){const th=node('th',title);th.scope='col';row.append(th);}head.append(row);table.append(head);const body=node('tbody');for(const values of block.rows){const tr=node('tr');for(const value of values)tr.append(node('td',value));body.append(tr);}table.append(body);wrap.append(table);parent.append(wrap);}
 else if(block.type==='code'){const wrap=node('div',undefined,'tutorial-code'),pre=node('pre'),code=node('code',block.text),button=node('button','Код хуулах');button.type='button';button.onclick=()=>void copy(block.text,button,'Хуулагдлаа');pre.append(code);wrap.append(button,pre);parent.append(wrap);}
 else if(block.type==='links'){const list=node('ul',undefined,'tutorial-reading-links');for(const item of block.items){const li=node('li'),a=node('a',item.label);a.href=item.url;a.target='_blank';a.rel='noopener noreferrer';li.append(a);list.append(li);}parent.append(list);}
}
async function copy(text,button,success){try{await navigator.clipboard.writeText(text);const previous=button.textContent;button.textContent=success;setTimeout(()=>button.textContent=previous,1800);}catch{$('tutorial-message').textContent='Хуулах боломжгүй байна. Код эсвэл browser-ийн холбоосыг гараар сонгож хуулна уу.';}}
function results(){
 const words=$('tutorial-search').value.trim().toLowerCase().split(/\s+/).filter(Boolean),category=$('tutorial-category').value;
 const matches=topics.filter(t=>(!category||t.category===category)&&words.every(w=>t.searchText.includes(w)));
 $('tutorial-count').textContent=matches.length+' / '+topics.length+' хичээл';$('tutorial-grid').replaceChildren();
 for(const t of matches){const link=node('a',undefined,'tutorial-card');link.href='#tutorial/'+t.id;link.append(node('p',t.category+' · '+t.level,'eyebrow'),node('h3',t.title),node('p',t.summary),node('small','Жишээ · Баталгаа · C++17 · Дасгал →'));$('tutorial-grid').append(link);}
 if(!matches.length)$('tutorial-grid').append(node('p','Тохирох хичээл олдсонгүй. Англи нэр эсвэл Монгол тайлбараар хайж үзээрэй.','muted'));
}
function build(t){
 const content=$('tutorial-content');window.MathJax?.typesetClear?.([content]);content.replaceChildren();$('tutorial-toc').replaceChildren(node('strong','Энэ хичээлд'));
 t.sections.forEach((section,i)=>{const sectionNode=node('section');sectionNode.id='tutorial-'+t.id+'-'+i;sectionNode.append(node('h3',section.title));for(const block of section.blocks)renderBlock(block,sectionNode);content.append(sectionNode);const link=node('a',section.title);link.href='#tutorial/'+t.id+'/part/'+i;link.onclick=event=>{event.preventDefault();sectionNode.scrollIntoView({behavior:'smooth',block:'start'});};$('tutorial-toc').append(link);});
 $('tutorial-related').replaceChildren(node('h3','Холбоотой сэдвүүд'));for(const id of t.related){const other=topics.find(x=>x.id===id);if(other){const a=node('a',other.title);a.href='#tutorial/'+other.id;$('tutorial-related').append(a);}}
}
function renderTopic(t){
 current=t;const turn=++renderTurn;$('tutorial-browser').hidden=true;$('tutorial-reader').hidden=false;$('tutorial-title').textContent=t.title;$('tutorial-meta').textContent=t.category+' · '+t.level;$('tutorial-summary').textContent=t.summary;$('tutorial-prerequisites').textContent='Урьдчилан мэдэх: '+t.prerequisites;$('tutorial-message').textContent='';document.title=t.title+' — Erdene Club';
 $('tutorial-content').setAttribute('aria-busy','true');
 mathQueue=mathQueue.then(async()=>{if(turn!==renderTurn)return;build(t);$('tutorial-title').focus({preventScroll:true});$('tutorial-title').scrollIntoView({block:'start'});$('tutorial-content').setAttribute('aria-busy','false');$('tutorial-math-message').textContent='Томъёог дүрсэлж байна…';$('tutorial-math-retry').hidden=true;
  try{const mj=await mathjax();if(turn!==renderTurn)return;await mj.typesetPromise([$('tutorial-content')]);if(turn===renderTurn)$('tutorial-math-message').textContent='';}
  catch(e){if(turn===renderTurn){$('tutorial-math-message').textContent=e.message+' Томъёог түр LaTeX хэлбэрээр харуулж байна.';$('tutorial-math-retry').hidden=false;}}
 }).catch(()=>{$('tutorial-message').textContent='Хичээлийг дүрслэхэд алдаа гарлаа. Дахин сонгоно уу.';});
}
function route(){
 if(!topics.length)return;
 const match=location.hash.match(/^#tutorial\/([a-z0-9-]+)(?:\/part\/(\d+))?$/);
 if(match){const t=topics.find(x=>x.id===match[1]);if(t){renderTopic(t);return;}$('tutorial-message').textContent='Энэ хичээлийн холбоос олдсонгүй. Жагсаалтаас сэдэв сонгоно уу.';}
 if(location.hash==='#tutorials'||match){++renderTurn;current=null;$('tutorial-browser').hidden=false;$('tutorial-reader').hidden=true;document.title=defaultTitle;results();}
}
async function init(){
 $('tutorial-search').addEventListener('input',results);$('tutorial-category').addEventListener('change',results);window.addEventListener('hashchange',route);
 $('tutorial-copy-link').onclick=()=>void copy(location.href,$('tutorial-copy-link'),'Холбоос хуулагдлаа');$('tutorial-math-retry').onclick=()=>{if(current)renderTopic(current);};
 try{const response=await fetch('./tutorials.json?v=11');if(!response.ok)throw new Error();const data=await response.json();if(!Array.isArray(data.tutorials)||!data.tutorials.length)throw new Error();topics=data.tutorials.map(t=>({...t,searchText:JSON.stringify(t).toLowerCase()}));for(const category of new Set(topics.map(t=>t.category))){const option=node('option',category);option.value=category;$('tutorial-category').append(option);}results();route();}
 catch{$('tutorial-grid').textContent='Tutorials ачаалсангүй. Хуудсаа дахин ачаалаарай.';$('tutorial-count').textContent='';}
}
void init();
