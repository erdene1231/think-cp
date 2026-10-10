# Tutorials — бүтэн, дэлгэрэнгүй хичээлийн шинэчлэлт

Энэ багцын хамгийн сүүлийн суулгах заавар нь **энэ файл**. Frontend cache v16,
tutorials.json version 6. Багц нь гараар суулгах зориулалттай; live GitHub эсвэл
Supabase-д автоматаар байршуулсан хувилбар биш.

## Юу өөрчлөгдсөн бэ?

43 DSA хичээлийн Монгол, English хувилбарыг хоёуланг нь дэлгэрүүлсэн.
Хичээл бүр 14 хэсэгтэй. Өмнөх 11 хэсгийн дугаар, part холбоос хадгалагдсан.

- Энгийн аргаас шинэ санаа гаргах, state болон invariant-ийн утгыг тайлбарлах.
- Илүү нарийн гараар хийсэн trace: хадгалсан утга алхам бүрт яаж өөрчлөгдөхийг үзүүлэх.
- Кодын variable, нөхцөл, recursion/loop-ийн үүргийг тодруулах.
- Зөв ажиллах нөхцөл, өөр арга сонгох шаардлага болон boundary test-үүд.
- **12-р хэсэг:** хэзээ хэрэглэх, яаж шалгах.
- **13-р хэсэг:** input format, sample input/output, шууд ажиллуулах бүтэн C++17 program.
- **14-р хэсэг:** гурван дасгал, тус тусдаа нээж/нууж болох hint ба хариу. Нийт 129 нэмэлт дасгал, хоёр хэлээр.

DP дээр state ба recurrence-ийг сүүлийн сонголтоос гаргана. Recursive segment
tree дээр disjoint/full/partial query-ийг ялгана. Lazy tree дээр sum аль хэдийн
шинэ, tag нь хүүхдэд дамжаагүй addition гэдгийг тайлбарлана. Dijkstra-ийн
nonnegative нөхцөл, KMP-ийн border/fallback, Fenwick-ийн block, LCA-ийн jump,
DSU-ийн representative зэрэг өмнө нь хурдан алгассан санааг дэлгэрүүлсэн.

“Бүтэн хичээл” болон “Хэсэг хэсгээр” гэсэн унших горим нэмсэн. Хэсэгчилсэн
горимд агуулгын жагсаалтаас сонгох эсвэл өмнөх/дараагийн товчоор шилжинэ.
Сонгосон горим хадгалагдана. Хэлээ солиход тухайн хэсэг хэвээр байна.

Математик болон variable notation MathJax-аар дүрслэгдэнэ. Өмнөх зарим TeX
escape-ийн зөрүүг зассан. C++ өнгөөр ялгагдана; sample I/O энгийн текстээр
харагдана. Бүх reference code 4-space indentation-тай, assert-гүй. Админ шинэ
хэсгүүдийн хоёр хэлний агуулга, sample, бүтэн program-ийг засаж, preview харна.

## Суулгах

1. ZIP-ийг задлаад repository-д ижил замаар файлуудыг нэмэх/солих.
   Өөрийн **config.js**, **problems.json**-ийг хадгална: ZIP эдгээрийг агуулаагүй.
   JSON problem importer руу tutorials.json оруулахгүй.
2. Supabase SQL Editor-д:
   - Өмнөх speed update буюу **011-tutorial-speed-explanations.sql** суусан бол
     зөвхөн **012-complete-tutorials.sql** ажиллуул.
   - 43 beginner lesson байгаа, 011 суулгаагүй бол эхлээд **011**, дараа **012**.
   - Хуучин 24 хичээлтэй бол эхлээд **010**, дараа **011**, эцэст **012**.
     010 default хичээлүүдийг шинэчилдэг; түүний суулгах зааврыг уншина.
   - Tutorial хүснэгт огт байхгүй бол account/admin/source-ийн өмнөх setup-ийн
     дараа багцын шинэ **008-tutorials.sql** ажиллуул. Энэ нь шууд хамгийн сүүлийн
     43 хичээлийг seed хийнэ. Fresh 008-ийн дараа 010/011 шаардлагагүй; 012-ийг
     ажиллуулсан ч ижил агуулгыг дахин өөрчлөхгүй.
3. GitHub-д өөрчлөлтөө commit хийж Pages deployment дууссаны дараа шалга.
   Tutorials → Segment tree → 12–14-р хэсэг; Монгол/English, хоёр унших горим,
   hint нээх/нуух, sample program-ийг туршина.

**Зөвхөн tutorials.json солих нь Supabase-д хадгалсан агуулгыг шинэчлэхгүй.
Өмнө tutorial хүснэгттэй бол 012 SQL-ийг ажиллуулна.** 012-ийн дараа хуучин
009/010/011-ийг дахин ажиллуулахгүй: өмнөх агуулгын хэсгүүдийг буцаан тавьж болно.

## Админ засвар, audit

012 нь default 43 ID-д үйлчилнэ. Өмнө тараасан агуулга яг хэвээр бол шинэ
хичээлээр сольдог. Админ өөрчилсөн бол тэр paragraph, code block, гарчиг,
summary, English текстийг хадгалж, өөрчлөгдөөгүй блокийг шинэчилнэ. Дэлгэрэнгүй
тайлбар болон 12–14-р хэсгийг нэмнэ. Шинэ хэсэгт дараа хийсэн админ засвар ч
012-ийг дахин ажиллуулахад хадгалагдана. Custom ID-тай хичээлүүдэд хүрэхгүй.

Алга болсон default ID-г шинэ агуулгаар нэмнэ. Өөрчлөгдсөн өмнөх body нь
tutorial_changes audit-д үлдэж revision нэмэгдэнэ. Давтан ажиллуулахад давхар
section, exercise эсвэл revision үүсэхгүй. Админ өөрөө code-ийн логикийг
өөрчилсөн бол шинэ жишээтэй нийцэж буйг шалгана; тэр custom кодыг хүчээр солихгүй.

## Шалгалт

- 43 хичээлийн хоёр хэлний schema, 14 хэсэг, prerequisite ба reference файлын нийцэл.
- 43 бүтэн program C++17-оор compile хийж, sample output бүрийг тулгасан.
- Бүх 43 program дээр 736 sample/boundary/random execution-ийг бие даасан жижиг
  brute-force, exhaustive permutation, энгийн array/graph тооцоотой харьцуулсан.
- Browser дээр хоёр хэлний 86 lesson-ийн MathJax, C++ highlighting, plain I/O,
  hint нээх/нуух; 14-section navigation, хэл солих, горим хадгалах, mobile layout.
- Admin edit/preview/save нь section key, collapsible hint, I/O төрөл, untouched
  English текстийг хадгалдаг.
- PostgreSQL/PGlite дээр fresh seed, хуучин хувилбарыг upgrade хийх, custom edits
  ба custom ID хадгалах, missing lesson сэргээх, audit, no-op rerun, ordinary-user
  write denial шалгасан.

Хичээлийн тайлбар, жишээ, дасгалыг Erdene Club-д зориулж бичсэн. Хичээл бүрийн
“Дараа нь юу сурах вэ?” хэсэгт CSES book, USACO Guide, CP-Algorithms зэрэг
нэмэлт унших эх сурвалжийн холбоос бий. Advanced сэдвүүд нь prerequisite-тэй;
DSU-ийн inverse-Ackermann bound-ийн бүрэн proof зэрэг нарийн өргөтгөлийг тусдаа
унших сэдэв болгон ялгасан.
