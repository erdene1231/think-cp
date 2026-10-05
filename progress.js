export const EMPTY = {status:'new', hints:0, notes:''};
export function cleanEntry(value) {
  if (!value || !['new','trying','solved'].includes(value.status) || !Number.isInteger(value.hints) || value.hints < 0 || value.hints > 3 || typeof value.notes !== 'string' || value.notes.length > 5000) throw new Error('Progress-ийн бүтэц буруу байна.');
  return {status:value.status,hints:value.hints,notes:value.notes};
}
export function parseBackup(value, ids) {
  if (value?.version !== 1 || !value.progress || Array.isArray(value.progress) || typeof value.progress !== 'object') throw new Error('Think CP-ийн progress файл сонгоно уу.');
  const result = {};
  for (const [id, entry] of Object.entries(value.progress)) {
    if (!ids.has(id)) throw new Error('Танихгүй бодлогын ID: '+id);
    result[id] = cleanEntry(entry);
  }
  return result;
}
