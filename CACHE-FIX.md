# Browser cache засвар

Шинэ JavaScript хуучин 24 бодлоготой problems.json-ийг cache-аас уншихад rating undefined болсон.

Засвар: JSON URL-д v=4 нэмсэн, fetch cache:no-store ашигласан. App, CSS, catalog module-ийн URLs шинэ хувилбарын дугаартай.

ZIP-ийг задлаад index.html, app.js гэсэн хоёр файлыг repository-ийн үндсэн хавтаст Upload files-аар оруулж commit хийнэ. Бусад файлыг солихгүй. Supabase SQL өөрчлөлт байхгүй.

Шууд түр засах: асуудалтай browser дээр Ctrl+Shift+R (эсвэл Ctrl+F5). Хэрэв хэвээр бол DevTools → Network → Disable cache сонгоод refresh. Site data/localStorage устгах шаардлагагүй.

Шалгалт: fetch URL болон cache option, каталогийн шүүлтүүрүүд, username/solver mock DOM regression давсан. Live browser шалгалт хийгдээгүй.
