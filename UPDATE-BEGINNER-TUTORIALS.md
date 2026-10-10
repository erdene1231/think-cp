> Энэ нь өмнөх шинэчлэлтийн тайлбар. Энэ багцыг суулгахдаа **UPDATE-COMPLETE-TUTORIALS.md**-ийн хамгийн сүүлийн зааврыг дагана.

> Хамгийн сүүлийн хурдны тайлбарын шинэчлэлт суулгах бол **UPDATE-TUTORIAL-SPEED.md**-ийн зааврыг дагаж, 011 SQL-ийг хамгийн сүүлд ажиллуулна. Доорх нь өмнөх beginner rewrite-ийн тайлбар.

# Erdene Club — beginner-friendly tutorial шинэчлэлт

Одоогийн 24 хичээлийн тайлбарыг бүрэн дахин бичиж, 19 шинэ сэдэв нэмсэн. Нийт 43 хичээл: 19 анхан, 20 дунд, 4 ахисан шат. Монгол/English агуулга бүрэн; MathJax болон C++ өнгөчлөл хэвээр.

## Суулгах

1. ZIP-ийг задлаад файлуудыг repository-д ижил замаар нэмэх/солих. `vendor`, `reference-code`, `reference-examples`, `supabase` хавтсуудыг хадгална. Өөрийн `config.js`, бодлогын JSON болон бусад файлыг хэвээр ашиглана.
2. Supabase → SQL Editor:
   - `008-tutorials.sql` өмнө ажиллуулсан бол **зөвхөн `010-beginner-tutorials.sql`** ажиллуул.
   - Tutorial хүснэгт хараахан үүсээгүй бол өмнөх `007-custom-sources.sql` суусан байх ёстой. Дараа нь энэ багцын `008-tutorials.sql`, эцэст нь `010-beginner-tutorials.sql` ажиллуул.
   - `009-readable-reference-code.sql` энэ шинэчлэлтэд шаардлагагүй. Шинэ 010-ийн дараа хуучин 009-ийг дахин ажиллуулахгүй.
3. GitHub-д commit хийгээд Pages deployment дуусахыг хүлээнэ. Browser-оо дахин нээгээд Tutorials хэсгээс 43 хичээл харагдаж байгааг шалгана. Frontend/JSON cache version нь v14.

Зөвхөн JSON солих нь Supabase-д хадгалсан хуучин хичээлүүдийг шинэчлэхгүй; 010 SQL хэрэгтэй. Энэ нь суулгах багц бөгөөд live GitHub/Supabase-д автоматаар байршуулсан хувилбар биш.

## Хичээлүүд хэрхэн өөрчлөгдөв?

Хичээл бүр: жижиг бодлого → энгийн loop/recursion арга → шинэ санаа → нэр томъёо → гараар хийх trace → алгоритмын алхмууд → C++ кодын тайлбар → зөв ажиллах шалтгаан ба complexity → алдаа → хариутай дасгал.

- Segment tree: recursive build/query/update, inclusive `[l,r]`. Query-ийн гурван тохиолдлыг жишээ бүрээр ялгасан. Дөрвөн элементтэй interactive tree дээр array/query-г өөрчилж туршиж болно.
- DFS: эхний reference нь recursive; маш гүн graph-д explicit stack хэрэглэх нөхцөлийг тайлбарласан.
- DP: rolling variables биш бүтэн dp array.
- Knapsack: эхлээд 2D хүснэгт, нэг item-ийг давтахгүй байх шалтгаан нь өмнөх мөрөөс уншихад ил харагдана.
- LIS: эхлээд O(n²) dp. O(n log n) optimization нь дараа сурах сэдэв.
- Combinatorics: эхлээд Pascal DP. Factorial болон modular inverse-ийг урьдчилан мэддэг гэж үзэхгүй.
- Prefix sum, difference array, 2D prefix sum, GCD, fast power, sieve-ийг тусдаа хичээл болгосон.
- Dijkstra-ийн өмнө priority queue-ийн тайлбар бий.
- Prerequisite холбоос, сурах дарааллын дугаар, өмнөх/дараагийн хичээл нэмсэн. Анхан шатнаас эхлэх заавар landing дээр байна.

Бүх reference code assert-гүй, дөрвөн space indentation-тай, нэг мөрөнд нэг үйлдэлтэй. `adj`, `dist`, `parent`, `mid`, `tree`, `lazy`, `dp`, `ans` зэрэг түгээмэл нэр хэрэглэнэ. Англи CP нэр томъёо хэвээр.

## Шинэ сэдвүүд

Sorting; brute force; recursion; stack/queue; set/map; bit operations; graph basics; flood fill; tree basics; difference array; 2D prefix sum; binary search on answer; grid DP; GCD; fast power; sieve; priority queue; Floyd–Warshall; Kruskal.

## Код ашиглах

`reference-code` дотор 43 function/data structure-ийн хэрэгжүүлэлт байна. Main-тайгаа холбож ашиглана. `reference-examples` дотор segment tree, DP, knapsack, LIS, grid DP, Fenwick, BFS, recursion, GCD, fast power-ийн 10 бүтэн program бий. Жишээ нь:

```bash
g++ -std=c++17 reference-examples/segment-tree.cpp -o segment-demo
./segment-demo
```

Хариу 8, дараагийн мөрөнд 13 гарна. Tutorial дээр function-ийн код ба жишээ main тусдаа copy button-тай харагдана.

Энэ багцад range sum, difference array, Fenwick, sparse table, segment tree, lazy tree-ийн public range-ууд inclusive `[l,r]`. Prefix(k) нь эхний k элементийн нийлбэр. Binary search-ийн доторх хайлтын хүрээ `[l,r)`; greedy киноны цаг мөн `[l,r)`. Хичээл бүр хэрэглэж буй заагаа тодорхой тайлбарлана.

Knapsack-ийн 2D болон Pascal-ийн хүснэгт нь санааг сурах reference. Хэт том capacity/хязгаарт optimization хэрэгтэй; complexity хэсгээ уншиж байж сонгоно.

## Хадгалсан админ засварууд

010 нь 24 default ID-ийн **бүтэн хичээлийг**, өмнөх admin засварыг оролцуулан шинэ хичээлээр солино. User-ийн хүссэн бүрэн найруулгын шинэчлэлт учраас зөвхөн code block солихгүй. Өмнөх body бүр `tutorial_changes.previous_body` audit-д үлдэнэ; revision нэмэгдэнэ. 19 шинэ ID-г нэмнэ. Default ID-уудаас өөр custom ID-г устгахгүй. Дахин ажиллуулахад ижил body дээр өөрчлөлт хийхгүй.

## Шалгалт

43 C++17 хэрэгжүүлэлтийг compile хийж, жишээ/randomized/brute-force хариутай тулгасан. 10 бүтэн program нь tutorial дээр бичсэн хариугаа хэвлэдэг. Browser дээр 86 Монгол/English хувилбарын MathJax, C++ өнгөчлөл, сурах дараалал, prerequisite холбоос, interactive tree, mobile, navigation, admin preview/save урсгалыг шалгасан. 010 SQL-ийг хуучин 24 хичээлтэй PostgreSQL/PGlite дээр ажиллуулж шинэ ID, revision/audit, custom ID хадгалалт, давтан ажиллуулалт болон ordinary-role write denial-ийг шалгасан.
