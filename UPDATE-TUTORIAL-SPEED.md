# Tutorial-ийн хурдны гол санаа — шинэчлэлт

43 хичээлийн Монгол, English хувилбарт **11. Яагаад ийм хурдан ажилладаг вэ?** гэсэн тусдаа хэсэг нэмсэн. Хичээлийн агуулгын жагсаалтаас шууд очно. Өмнөх 10 хэсгийн дугаар, холбоос өөрчлөгдөхгүй.

Хэсэг бүр тухайн кодын:

- давтагдсан ямар ажлыг хэмнэж байгааг;
- нийт loop, call, state, transition, node эсвэл edge хэдэн удаа боловсруулагдахыг;
- тэр тооллогоос complexity яаж гарахыг;
- гараар шалгаж болох тоон жишээг;
- уг хурд ямар нөхцөлд хүчинтэй, ямар зардал үлдэж байгааг тайлбарлана.

Жишээлбэл two pointers, monotonic stack, KMP дээр доторх while-ийн **бүх iteration-ийн нийлбэр** linear байдгийг; segment tree дээр түвшин бүрт зөвхөн хоёр зааг орчмын node-ууд цааш задардгийг; DP дээр **state-ийн тоо × нэг state-ийн ажил** гэдгийг тайлбарласан. LIS-ийн reference O(n²), Fenwick-ийн энэ build O(n log n), bitmask DP exponential хэвээр гэдгийг ил тод ялгана. DSU-ийн doubling тайлбар O(log n)-ийг нотолдог, inverse Ackermann-ийн бүрэн баталгаа тусдаа нарийн сэдэв болохыг тэмдэглэнэ. Sieve-ийн repeated marking ба reciprocal-prime bound-ийг ялгана.

Time complexity хичээлийн count_pairs кодонд өөртэй нь хослуулж тоолсон зөрүү байсан. Одоо j = i + 1-ээс n хүртэл шалгаж, тайлбар дахь n(n−1)/2 хостой нийцсэн. Бусад reference implementation-ийг энэ шинэчлэлт өөрчлөөгүй.

## Суулгах

1. ZIP-ийн файлуудыг repository-д ижил замаар нэмэх/солих. Өөрийн **config.js**, **problems.json**-ийг хадгална; эдгээрийг ZIP-д оруулаагүй.
2. Supabase SQL Editor-д:
   - Өмнөх 43 beginner-friendly хичээлтэй **010-beginner-tutorials.sql** суусан бол зөвхөн **011-tutorial-speed-explanations.sql** ажиллуулна.
   - Tutorial хүснэгт байгаа боловч хуучин 24 хичээлтэй бол эхлээд **010**, дараа **011** ажиллуулна. 010 нь default хичээлийн өмнөх агуулгыг шинэчилдэг тул тухайн файлын зааврыг уншина.
   - Tutorial хүснэгт үүсээгүй бол өмнөх account/admin/source migrations суусан байх ёстой. Дараа багцын **008-tutorials.sql**, эцэст нь **011-tutorial-speed-explanations.sql** ажиллуулна. Энэ шинэ 008 нь шууд хамгийн сүүлийн 43 хичээлийг seed хийнэ.
3. GitHub-д commit хийж Pages deployment дуусахыг хүлээнэ. Frontend cache v15, tutorials JSON version 5. Tutorials дотор дурын хичээлийн 11-р хэсгийг Монгол, English хэлээр шалгана.

**Зөвхөн tutorials.json солих нь Supabase-д байгаа агуулгыг өөрчлөхгүй. 011 SQL-ийг ажиллуулах шаардлагатай.** 011-ийн дараа хуучин 009 эсвэл 010-ийг дахин ажиллуулахгүй: тэд өмнөх агуулгаа буцаан тавьж болно.

## Админ засвар ба audit

011 нь default ID-тай байгаа хичээлийн бусад хэсэг, гарчиг, metadata-г хадгалж, зөвхөн speed-reason key-тай шинэ хэсгийг хоёр хэлээр нэмнэ/шинэчилнэ. Алга болсон default ID-г шинэ бүтэн агуулгаар нэмнэ. Custom ID-г өөрчлөхгүй. Өмнөх body tutorial_changes audit-д хадгалагдаж revision нэмэгдэнэ; ижил migration-ийг давтахад revision дахин нэмэгдэхгүй.

Хос тоолох кодын засварыг **өмнө тараасан буруу code block яг хэвээр байгаа үед л** хийнэ. Админ өөрөөр өөрчилсөн code block-ийг автоматаар солихгүй. Тийм custom код байвал хурдны тайлбартай нь нийцэж байгаа эсэхийг админ нягтална. Шинэ хэсгийг одоогийн admin tutorial editor-оор засаж болно.

Энэ ZIP нь гараар суулгах шинэчлэлтийн багц; live GitHub/Supabase-д автоматаар байршуулсан хувилбар биш.

## Шалгасан зүйлс

- 43 хичээлийн schema, хоёр хэлний 86 шинэ хэсэг, math delimiter-үүд; reference-code ба embedded primary code-ийн нийцэл.
- Зассан хос тоолох C++ reference-ийг compile/run хийж boundary ба жишээ input дээр хосын томъёотой тулгасан.
- Тайлбарын тоон жишээнүүдийг шалгаж, segment tree-ийн түвшин бүрийн хамгийн ихдээ дөрвөн node visit-ийг 3411 query range дээр баталгаажуулсан.
- Browser дээр 86 Монгол/English хувилбарын бодит MathJax, C++ highlighting, 11 TOC холбоос; хуучин part route, mobile layout.
- Admin edit/preview/save урсгал шинэ хэсгийн key болон өөрчлөгдөөгүй English тайлбарыг хадгалдаг.
- PostgreSQL/PGlite дээр fresh seed, хуучин агуулгад нэмэх migration, custom content/ID хадгалах, алга болсон default ID нэмэх, revision/audit, давтан ажиллуулахад no-op, ordinary-role write denial.
