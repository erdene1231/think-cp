# JSON import болон бусдыг админ болгох

## Суулгах

Өмнөх Following/Admin шинэчлэлт (`004-following-admin.sql`) суусан байх шаардлагатай.

1. Supabase → SQL Editor дээр `supabase/005-json-import-admins.sql` файлыг бүхэлд нь хуулж Run дарна. Дахин ажиллуулахад одоогийн админ, бодлогууд хадгалагдана.
2. ZIP-ийн 9 web файлыг repository-ийн үндсэн хавтсанд нэмэх/солих: `index.html`, `styles.css`, `app.js`, `admin.js`, `problem-store.js`, `social.js`, `catalog.js`, `problems.json`, `problem-import-example.json`.
3. Commit хийгээд GitHub Pages шинэчлэгдэхийг хүлээнэ. Одоогийн `config.js`-ийг хэвээр үлдээнэ. Admin account-аар нэвтэрч Admin хэсгийг нээнэ.

SQL-ийг repository-д upload хийх нь Supabase дээр ажиллуулахгүй. 005 migration-ийг SQL Editor дээр ажиллуулна. Энэ багцыг бодит Supabase/GitHub Pages дээр хараахан суулгаагүй.

## JSON-оор нэг эсвэл олон бодлого нэмэх

Admin → “JSON-оор бодлого нэмэх” → JSON файл сонгох → preview-ийг шалгах → “Бодлогуудыг нэмэх”. Файл сонгоход шууд хадгалахгүй.

Дэмжих 3 бүтэц:

- Нэг бодлогын object: `{ "title": "...", ... }`
- Бодлогын array: `[{ ... }, { ... }]`
- Catalog бүтэц: `{ "problems": [{ ... }, { ... }] }`

Нэг удаад 1–100 бодлого, файл 2 MB хүртэл. `problem-import-example.json` нь нэг бодлоготой загвар; сайт дээрээс татаж болно. Загварын `example.com` холбоосыг жинхэнэ бодлогын холбоосоор, бусад мэдээллийг тухайн бодлогод тохируулж солино. Олон бодлого оруулахдаа `problems` array-д object-ууд нэмнэ.

Бодлогын шаардлагатай талбарууд:

| Талбар | Утга |
| --- | --- |
| title | Бодлогын нэр, 1–200 тэмдэгт |
| source | Codeforces, CSES, EGOI эсвэл Other |
| ref | Эх бодлогын ID, 1–80 тэмдэгт |
| url | HTTPS бодлогын холбоос |
| rating | 800–4000 бүхэл тоо |
| ratingKind | official эсвэл estimated; official зөвхөн Codeforces |
| priority | true эсвэл false |
| tags | 1–20 English tag бүхий array |
| hints | Монгол 3 hint бүхий array |
| hintsEn | English 3 hint бүхий array |
| lesson | Бодсоны дараах тайлбар, 1–2000 тэмдэгт |
| level | Practice эсвэл Interactive; орхивол Practice |
| editorialUrl | Сонголттой HTTPS editorial холбоос |

Файлд байгаа `id`, `number`, `pack`, `revision`, `archived` талбарууд import-д ашиглагдахгүй. Бодлого бүр шинэ ID авна, дугаар файлын array дахь дарааллаар олгогдоно. Import нь шинэ бодлого нэмэх зориулалттай; өмнөх бодлого засахдаа editor-ийг ашиглана.

Ижил URL эсвэл ижил source + ref-тэй бодлогыг давхардсан гэж үзнэ. Хассан бодлого ч энэ шалгалтад орно. Түүнийг дахин import хийхийн оронд сэргээж болно. Файл дотор давхардсан бодлого эсвэл дутуу hint байвал preview алдааг харуулна. Database мөн бүх бодлогыг дахин шалгана: аль нэг нь буруу/давхардсан бол **багцыг бүхэлд нь буцаана**. Өмнөх ID өөрчлөгдөхгүй; буцаагдсан transaction sequence-ийн дугаарыг алгасаж болно.

## Бусдыг админ болгох

Admin → “Админ эрх олгох” → username оруулах → “Хэрэглэгч олох” → гарсан username, нэр, сургуулийг шалгах → “Админ болгох”. Email оруулахгүй.

Шинэ админ дахин нэвтрэх эсвэл хуудсыг reload хийхэд Admin хэсэг гарна. Бодлого нэмэх, JSON import, засах, хасах/сэргээх болон бусдад админ эрх олгох боломжтой. Админуудын жагсаалтыг энэ хэсэгт харуулна. Аль хэдийн админ хүнийг дахин нэмэхэд давхар бүртгэхгүй.

Эрх олгохыг database дээр зөвхөн одоогийн админ гүйцэтгэнэ; browser дахь email эсвэл metadata нь эрх өгөхгүй. Хэрэглэгчийн UUID-д эрх холбоно, хэн хэнд эрх олгосныг audit хүснэгтэд хадгална. Үндсэн админ хэвээр үлдэнэ. Энэ шинэчлэлтэд админ эрх цуцлах UI нэмээгүй.

## Шалгалт

- PostgreSQL-compatible PGlite: repeatable migrations, anon/энгийн хэрэглэгчийн эрхийн хориг, бүхэл багц rollback, duplicate болон 100 бодлогын хязгаар, автоматаар ID, admin grant idempotence/audit, шинэ админ бусдыг админ болгох болон import хийх.
- Жинхэнэ Chromium + mock Supabase: буруу JSON/hint, нэг object болон олон бодлогын preview/import, давхардсан upload, хүний мэдээлэл харуулж эрх олгох, шинэ admin login, өмнөх CRUD/following/profile/recovery/hint үйлдлүүд, mobile layout.
