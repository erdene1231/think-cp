export function ratingLabel(problem) {
  return (problem.ratingKind==='estimated'?'≈ ':'')+problem.rating;
}
export function getTags(problems) {
  return [...new Set(problems.flatMap(p=>p.tags))].sort((a,b)=>a.localeCompare(b));
}
export function filterProblems(problems, progress, filters) {
  const words=(filters.query||'').trim().toLowerCase().split(/\s+/).filter(Boolean);
  const band=filters.ratingBand?filters.ratingBand.split('-').map(Number):null;
  const result=problems.filter(p=>{
    const e=progress[p.id]||{status:'new',hints:0};
    const haystack=[p.title,p.ref,p.id,...p.tags].join(' ').toLowerCase();
    return (!filters.pack||p.pack===filters.pack)
      &&(!filters.source||p.source===filters.source)
      &&(!filters.tag||p.tags.includes(filters.tag))
      &&(!filters.priorityOnly||p.priority)
      &&(!band||(p.rating>=band[0]&&p.rating<=band[1]))
      &&(!filters.status||(filters.status==='hinted'?e.hints>0:e.status===filters.status))
      &&words.every(word=>haystack.includes(word));
  });
  return result.sort((a,b)=>{
    if(filters.sort==='title')return a.title.localeCompare(b.title)||a.id.localeCompare(b.id);
    if(filters.sort==='priority'&&a.priority!==b.priority)return Number(b.priority)-Number(a.priority);
    return (filters.sort==='rating-desc'?b.rating-a.rating:a.rating-b.rating)||a.title.localeCompare(b.title)||a.id.localeCompare(b.id);
  });
}
