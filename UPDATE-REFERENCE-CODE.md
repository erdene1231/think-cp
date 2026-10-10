# Beginner-friendly reference code шинэчлэлт

24 хичээлийн бүх reference C++ кодыг дахин бичсэн. Монгол болон English хувилбар ижил шинэ код харуулна.

## Суулгах

1. ZIP-ийг задлаад файлуудыг repository-ийн үндсэн хавтаст ижил замаар оруулж солино. vendor, supabase, reference-code хавтсуудын бүтцийг хэвээр хадгална. Өөрийн config.js-ийг ашиглана.
2. Өмнөх bilingual tutorial шинэчлэлт суусан бол Supabase → SQL Editor дээр supabase/009-readable-reference-code.sql-ийг ажиллуулна.
3. Хэрэв 008-tutorials.sql хараахан ажиллуулаагүй бол эхлээд 008, дараа нь 009 файлыг ажиллуулна. 008 нь өмнөх 007 migration суусан байхыг шаарддаг.
4. Commit changes хийж GitHub Pages deployment дууссаны дараа сайтаа дахин нээнэ. Browser-ийн хуучин JSON cache-г шинэчлэхийн тулд энэ багц v13 ашиглаж байгаа.

Зөвхөн tutorials.json-ийг солих нь Supabase-д өмнө хадгалсан reference code-ийг шинэчлэхгүй. Онлайн хичээлүүдийг өөрчлөх алхам нь 009 SQL юм.

## Coding style

- Дөрвөн space indentation; operator, comma, condition-ийн spacing жигд.
- Нэг мөрөнд нэг үйлдэл. If, else, for, while-ийн body бүр хаалттай.
- Assert байхгүй. Хэрэглэх нөхцөл болон input-ийн шаардлагууд tutorial-ийн тайлбарт байна.
- adj, dist, parent, mid, tree, lazy, bit, dp, ans, pref, diff, fact, invFact зэрэг түгээмэл нэртэй.
- Олон үйлдэл агуулсан increment, шахсан constructor, nested нэг мөрийн loop-уудыг салгасан.
- Monotonic stack болон DFS нь std::stack ашиглана. DSU нь union by size болон recursive path compression ашиглана.
- Topological sort нь bool буцаадаг бөгөөд order vector-ийг хоёр дахь параметрээр авна. True үед зөв дараалал, false үед cycle байна. False үед order хоосорно.
- Difference array update нь tuple-ийн оронд l, r, x талбартай Update struct ашиглана.

Reference code-уудыг reference-code хавтаст 24 тусдаа .cpp файл болгож мөн хавсаргасан. Эдгээр нь function эсвэл data structure-ийн хэрэгжүүлэлт; өөрийн main функцээс дуудан ашиглана. GNU C++17-д зориулсан. Number theory-ийн modpow үржвэрийн overflow-оос хамгаалахын тулд __int128 хэрэглэдэг.

## Хадгалсан хичээлүүд

009 SQL нь 24 үндсэн хичээлийн эхний reference code block-ийг хоёр хэл дээр шинэ кодоор солино. Хичээлийн ID, түвшин, дараалал, title болон админы өөрөө бичсэн тайлбаруудыг хадгална. Хуучин default тайлбартай яг таарч буй, code нэр болон API-г тайлбарласан хэсгүүдийг шинэ хэрэгжүүлэлттэй нийцүүлнэ.

Өөрчлөлт бүр revision болон audit-д бүртгэгдэнэ. 009-ийг дахин ажиллуулахад аль хэдийн шинэ хувилбар болсон хичээлүүд дахин өөрчлөгдөхгүй. Энэ migration нь reference code-ийг шинэчлэх тул эдгээр code block дээр хийсэн өмнөх админ засварыг мөн шинэ кодоор солино.

## Шалгалт

Бүх 24 хэрэгжүүлэлтийг g++ -std=c++17-аар compile хийж, тогтмол жишээ болон naive/brute-force/randomized reference хариутай тулгасан. Binary search, window, greedy, monotonic stack, Fenwick, segment tree, lazy tree, Dijkstra, LCA, knapsack, LIS, KMP, bitmask assignment, combinatorics зэрэгт харьцуулалтын шалгалт хийсэн.

Browser дээр нийт 48 Монгол/English хувилбарын шинэ код, C++ өнгөчлөл, MathJax болон хуучин navigation/admin урсгалуудыг шалгасан. SQL migration-ийг PostgreSQL/PGlite дээр хуучин 24 хичээлээс шинэ хувилбар руу шилжүүлж, admin title/тайлбар хадгалагдах, audit/revision үүсэх болон дахин ажиллуулахад өөрчлөлтгүй байхыг шалгасан.

Энэ нь суулгах багц; GitHub болон live Supabase-д автоматаар байршуулсан хувилбар биш.
