# Бодлогын сангийн шинэчлэл

84 бодлого: Codeforces 73, CSES 10, EGOI 1. Өмнөх 24 дээр 60 шинэ бодлого нэмсэн.
Rating 900–2500, 30 priority бодлого ★ одтой. Бодлого бүр 3 шаталсан hint-тэй.

## GitHub дээр оруулах

1. ZIP-ийг задла.
2. https://github.com/erdene1231/think-cp дээр **Add file → Upload files** сонго.
3. Дараах 5 файлыг repository-ийн үндсэн хавтас руу оруулж, өмнөх ижил нэртэй файлуудыг шинэчил:
   - index.html
   - styles.css
   - app.js
   - catalog.js (шинэ файл, заавал хамт оруул)
   - problems.json
4. **Commit changes** дар. GitHub Pages build дууссаны дараа хуудсаа refresh хий. Хуучин харагдвал hard refresh хий.

config.js, progress.js, community.js болон supabase/ файлуудыг солих шаардлагагүй.
Supabase SQL дахин ажиллуулах шаардлагагүй. Өмнөх 24 бодлогын ID хэвээр.

## Шинэ боломжууд

- Нэр, ID болон English tag-аар хайна. Олон үг оруулбал бүгдийг нь агуулсан бодлогууд гарна.
- Tag, rating, эх сурвалж, багц, миний төлөв, priority шүүлтүүрүүд хамт ажиллана.
- Rating өсөх/буурах, priority эхэнд, нэрээр эрэмбэлнэ.
- Priority бодлогын нэрийн өмнө ★ харагдана.
- Tags харуулах сонголттой. Бодлогын цонхонд Tags харуулах товч мөн бий. Бодсон үед tags автоматаар харагдана.
- Codeforces rating нь 2026-10-05-нд албан problemset API-тай тулгасан утга. Дараа нь өөрчлөгдөж болно.
- CSES/EGOI-д албан CF rating байхгүй тул ≈ тэмдэгтэй сургалтын баримжаа тавьсан.
- Hint-д binary search, grid, dp, array, prefix sums зэрэг technical terms-ийг English хэвээр үлдээсэн.
- Албан editorial холбоос олдсон бодлогод бодсоны дараах хэсэгт холбоос гарна.

## Шалгалт

- 84 unique ID, 30 priority, бүх 73 CF title/rating, бүх 252 hint, English tags шалгасан.
- Өмнөх 24 ID хадгалагдсан; HTML ID-ууд болон JS references шалгасан.
- Query/tag/source/rating/priority/status хосолсон шүүлтүүр, sort, reset, tags rendering шалгасан.
- Username save, давхардсан username, solver pagination, solved/trying update, error/retry, stale response, account isolation regression шалгасан.
- 1450D, 1486D, 1661B, 1605C, 1392D, 1389B, 1479C, 1406D, 1644D-ийн hint-д тайлбарласан санааг exhaustive эсвэл brute-force харьцуулалтаар шалгасан.
- JavaScript syntax шалгалт давсан.
- Автомат UI шалгалт нь mock DOM ашигласан; жинхэнэ browser-ийн visual болон live Supabase end-to-end шалгалт энэ орчинд хийгдээгүй.

GitHub-ийн одоогийн холболт write үйлдэлд 403 буцаасан тул энэ ZIP сайтад автоматаар нийтлэгдээгүй.
