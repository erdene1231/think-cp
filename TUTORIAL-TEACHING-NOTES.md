# Сургалтын тайлбаруудын судалгаа ба хэрэглэсэн шийдлүүд

Судалсан огноо: 2026-10-10. Эдгээр нь эх сурвалжийн тайлбарыг харьцуулан уншаад гаргасан сургалтын шийдвэрүүд; сайт дээрх тайлбаруудыг хуулж орчуулаагүй.

| Эх сурвалж | Ажигласан арга | Erdene Club-д хэрэглэсэн нь |
| --- | --- | --- |
| [USACO Guide: Bronze](https://usaco.guide/bronze) | Суурь complete search болон sorting зэрэг сэдвүүдийг эхэлж үздэг | Brute force, sorting-ийг graph, DP-ээс өмнө оруулсан |
| [Introduction to Complete Search](https://usaco.guide/bronze/intro-complete) | Тодорхой бодлогын candidate-уудыг loop-оор шалгаж, index болон давхар тооллогын учрыг тайлбарладаг | Хосын жижиг бодлого, давхардал ба ижил index-ийн алдаа |
| [Introduction to Prefix Sums](https://usaco.guide/silver/prefix-sums) | Focus problem, жижиг array хүснэгт, naive зардал, prefix хасалтын жишээ | Жижиг array, prefix хүснэгт, inclusive query-ийн бодит тооцоо |
| [CP Algorithms: Segment tree](https://cp-algorithms.com/data_structures/segment_tree.html) | Simple range sum-аас эхлээд tree structure, recursive build/query/update; advanced хувилбаруудыг дараа нь үздэг | Эхний tree хичээл зөвхөн recursive point assignment + sum; query-ийн 3 тохиолдол; lazy тусдаа ахисан хичээл |
| [USACO Guide: Introduction to DP](https://usaco.guide/gold/intro-dp) | Жижиг subproblem/state-уудаар том хариу байгуулах санаа | State-ийг нэг өгүүлбэрээр тодорхойлж, base case ба transition-ийг тусад нь тайлбарласан |
| [Competitive Programmer’s Handbook](https://cses.fi/book/book.pdf) | Complete search, greedy, DP, range queries, graph/tree зэрэг сэдвийг жишээ ба кодоор холбодог | Сэдвийн prerequisite дараалал, жижиг trace, зөв ажиллах шалтгаан, complexity |

## Тайлбар бичих дүрэм

1. Эхний догол мөрөнд нэг л жижиг зорилго. Шинэ сурагч бүх алгоритмын нэр томъёог урьдчилан мэддэг гэж үзэхгүй.
2. Энгийн loop эсвэл recursion эхлээд. Ямар ажил давтагдаж, шинэ арга юу хадгалахыг дараа нь харуул.
3. Array-ийн index, range-ийн зааг, state болон variable-ийн утгыг тодорхой бич.
4. Жишээний тоонуудыг кодтой яг нийцүүл. Trace-г уншигч гараар давтаж чадахаар өг.
5. Optimization-ийг эхний implementation болгохгүй. 2D knapsack/Pascal, энгийн LIS/recursive tree бол эхлэлийн хувилбар.
6. Ахисан сэдвийг beginner гэж нэрлэхгүй; prerequisite холбоос өгч, хэрэгтэй суурь мэдлэгийг ил болго.
7. Дасгалын хариуг жижиг note-д өгч өөрөө шалгах боломжтой болго. Бодит task-ийн representation өөр бол ялгааг нь тайлбарла.

## Багшийн хэрэглээ

Бүгдийг дарааллаар нь заавал нэг дор заах шаардлагагүй. Анхан шатны array/search хичээлүүдээс эхлээд сурагч жижиг input-ийг гараар бодож, naive ба шинэ аргын ялгааг тайлбарлаж чадаж байгаа эсэхийг хар. Graph руу орохын өмнө adjacency list, queue, recursion-ийг шалга. DP дээр state-ийг хэлж чадахгүй бол transition цээжлүүлэхээс өмнө жишээ рүү буц.

Segment tree-ийн interactive demo query-ийн recursion-ийг дүрсэлнэ. Array утга өөрчлөхөд жижиг tree-г rebuild хийнэ; production reference code-ийн point update нь leaf рүү ганц замаар явж ancestor sum-уудыг шинэчилдэг. Өнгө: ногоон бүтнээр авсан, шар хэсэгчлэн задалсан, саарал давхцахгүй. Цагаан node нь тэр query-д очоогүй.

## Хурдны шалтгааныг тайлбарлах шинэ шаардлага

Хичээл бүрийн 11-р хэсэгт ажил хэмнэж буй санаа, үйлдлийн тооллого, Big O-ийн гаргалгаа, тоон жишээ, хүчинтэй нөхцөл орно. Хурдны санааг зөвхөн нэр эсвэл complexity-оор дүгнэхгүй. Nested loop-ийг хараад шууд үржүүлэхгүй; pointer-ийн нийт хөдөлгөөн, state/transition, heap entry, subtree-ийн зогсох нөхцөл зэрэг кодын бодит ажлыг тоолно.

Хугацааны тооллогын нарийн баримтуудыг дараах primary тайлбаруудтай тулгасан. Шинэ хичээлийн найруулга, тоон жишээнүүдийг тусад нь бичсэн.

- Segment tree: https://cp-algorithms.com/data_structures/segment_tree.html — нэг түвшний хязгаарлагдмал node visit.
- DSU: https://cp-algorithms.com/data_structures/disjoint_set_union.html — size doubling ба amortized bound-ийн ялгаа.
- KMP: https://cp-algorithms.com/string/prefix-function.html — prefix length-ийн нийт өсөлт/бууралтаар linear ажил тоолох.
- Sieve: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html — prime тус бүрийн n/p тэмдэглэгээний нийлбэр; composite давтан тэмдэглэгдэх боломжтой.
- GCD: https://cp-algorithms.com/algebra/euclid-algorithm.html — үлдэгдлээр хурдан жижигрүүлэх.

Нэг үйлдэл дээр удаан байж болох ч олон үйлдлийн нийт зардал бага байдгийг amortized жишээнүүд дээр тусад нь хэлнэ. DSU-ийн inverse Ackermann, sieve-ийн reciprocal-prime bound-ийн бүрэн нарийн баталгааг beginner intuition-тай андуурахгүй.
