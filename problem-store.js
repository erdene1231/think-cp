export function validateProblem(input) {
 const p={title:String(input.title||'').trim(),source:input.source,ref:String(input.ref||'').trim(),url:input.url,rating:Number(input.rating),ratingKind:input.ratingKind,level:input.level||'Practice',priority:input.priority===true,tags:[...new Set((input.tags||[]).map(t=>String(t).trim().toLowerCase()).filter(Boolean))],hints:input.hints,hintsEn:input.hintsEn,lesson:String(input.lesson||'').trim()};
 if(!p.title||p.title.length>200||!p.ref||p.ref.length>80)throw new Error('Бодлогын нэр болон эх бодлогын ID-гаа шалгана уу.');
 if(!['Codeforces','CSES','EGOI','Other'].includes(p.source))throw new Error('Эх сурвалж сонгоно уу.');
 const validUrl=s=>{try{const u=new URL(s);return u.protocol==='https:'&&!u.username&&!u.password&&String(s).length<=1000&&!/\s/.test(s);}catch{return false;}};
 if(!validUrl(p.url))throw new Error('HTTPS бодлогын холбоос оруулна уу.');
 if(input.editorialUrl){if(!validUrl(input.editorialUrl))throw new Error('Editorial HTTPS холбоос байх ёстой.');p.editorialUrl=input.editorialUrl;}
 if(!Number.isInteger(p.rating)||p.rating<800||p.rating>4000)throw new Error('Rating 800–4000 хүрээнд байна.');
 if(!['official','estimated'].includes(p.ratingKind)||(p.ratingKind==='official'&&p.source!=='Codeforces'))throw new Error('Rating-ийн төрлийг зөв сонгоно уу.');
 if(!['Practice','Interactive'].includes(p.level))throw new Error('Бодлогын төрөл сонгоно уу.');
 if(p.tags.length<1||p.tags.length>20||p.tags.some(t=>!/^[a-zA-Z0-9 +/&()_-]{1,50}$/.test(t)))throw new Error('1–20 English tag оруулна уу; tag тус бүр 50 тэмдэгт хүртэл.');
 for(const hints of [p.hints,p.hintsEn])if(!Array.isArray(hints)||hints.length!==3||hints.some(h=>typeof h!=='string'||!h.trim()||h.length>3000))throw new Error('Хэл тус бүрд 3 hint, hint бүр 1–3000 тэмдэгт байна.');
 if(!p.lesson||p.lesson.length>2000)throw new Error('Бодсоны дараах тайлбар 1–2000 тэмдэгт байна.');
 return p;
}
export function parseCatalog(document) {
 if(!document||!Array.isArray(document.problems)||!Array.isArray(document.knownIds))throw new Error('Бодлогын сангийн хариу буруу байна.');
 const ids=new Set(),numbers=new Set();
 for(const p of document.problems){validateProblem(p);if(typeof p.id!=='string'||!/^[a-zA-Z0-9_-]{1,100}$/.test(p.id)||ids.has(p.id)||!Number.isSafeInteger(p.number)||p.number<1||numbers.has(p.number))throw new Error('Бодлогын ID давхардсан эсвэл буруу байна.');ids.add(p.id);numbers.add(p.number);}
 if(document.knownIds.some(id=>typeof id!=='string'||!/^[a-zA-Z0-9_-]{1,100}$/.test(id))||[...ids].some(id=>!document.knownIds.includes(id)))throw new Error('Бодлогын ID жагсаалт буруу байна.');
 return document;
}
export function hintTexts(problem,language) {return language==='en'?problem.hintsEn:problem.hints;}
