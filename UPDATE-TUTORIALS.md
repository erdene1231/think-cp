# Erdene Club — Tutorials шинэчлэлт

## Суулгах

Энэ багц өмнөх Source / Pagination шинэчлэлттэй сайтад зориулагдсан.

1. ZIP-ийн index.html, app.js, styles.css, favicon.svg файлуудыг repository-ийн root түвшинд хуучин файлуудын оронд оруул.
2. tutorials.js, tutorials.json хоёр шинэ файлыг мөн root түвшинд оруул. JSON-ийг Supabase-ийн бодлогын importer-аар оруулахгүй; энэ нь tutorial-ийн агуулга.
3. Commit changes хийгээд GitHub Pages deployment дууссаны дараа сайтаа дахин нээ.
4. Tutorials цэсийг дар. English эсвэл Монгол үгээр хайж, бүлгээ сонгоод хичээл нээнэ.

Tutorials-д шинэ SQL migration шаардлагагүй. Өмнөх 007 Source шинэчлэлт суусан байх ёстой. Энэ ZIP нь config.js агуулахгүй тул өөрийн Supabase тохиргоогоо ашиглана.

## Сайтын нэр ба URL

Харагдах нэр, browser title, logo нь Erdene Club болсон. Кодын файлууд relative URL ашиглана.

GitHub Pages URL-ыг /erdene-club/ болгохын тулд repository → Settings → General → Repository name хэсэгт erdene-club гэж Rename хийнэ. Үүнийг энэ багц автоматаар хийгээгүй.

Шинэ хаяг https://erdene1231.github.io/erdene-club/ болно. Repository-ийг rename хийсэн бол Supabase → Authentication → URL Configuration дээр Site URL болон Redirect URLs-д шинэ хаягаа тохируул. Account-ын database болон бодлогын ID өөрчлөгдөхгүй. Browser хадгалалтын key-үүдийг өмнөх хэвээр ашиглаж progress-ийг хадгалсан.

## Tutorials

24 хичээлтэй. Хичээл бүр 10 хэсэгтэй: гол ойлголт, хэрэглэх нөхцөл, санаа/томъёо, алхамтай жишээ, correctness, C++17, time/space complexity, алдаа, дасгал, цааш унших холбоос.

- Суурь: Time & space complexity.
- Array/search: Prefix sum & difference array, Binary search, Two pointers, Sorting & greedy.
- Data structures: Stack/queue/monotonic stack, Hash map & compression, DSU, Fenwick tree, Segment tree, Sparse table, Lazy propagation.
- Graphs: BFS, DFS, Dijkstra, Topological sort/DAG DP, Binary lifting/LCA.
- DP: Dynamic programming, 0/1 knapsack, LIS, Bitmask DP.
- Strings: Prefix function/KMP.
- Math: GCD/sieve/modulo, Combinatorics ба түгээмэл томъёо.

Тайлбарууд нь Erdene Club-д зориулсан Монгол агуулга. Техникийн танил нэр томъёог англиар хадгалсан. C++ кодын нэг хэсэг нь GNU C++17-ийн __int128 хэрэглэдэг; number theory хичээлд энэ нөхцөлийг тайлбарласан.

Хайлтыг нэр, keyword, Монгол тайлбар, агуулгаас хийнэ. Хичээлүүд #tutorial/binary-search хэлбэрийн өөрийн холбоостой; reload ба Back/Forward ажиллана. Код, холбоос хуулах товчтой.

## Математикийн томъёо

MathJax 3.2.2 SVG renderer-ийг Tutorials хичээл анх нээхэд CDN-ээс ачаална. Хичээлүүдийн formulas нь tutorials.json дотор type=math, tex талбарт LaTeX байна. Inline \( … \), block \[ … \], $ … $, $$ … $$ delimiter-ууд дэмжинэ. Code block доторх текстийг MathJax өөрчлөхгүй.

Renderer-ийн CDN хүрэхгүй үед тайлбар ба код уншигдсан хэвээр, томъёо LaTeX хэлбэрээр харагдаж, дахин ачаалах товч гарна. Tutorials-ийн текст, код нь account нэвтрэх шаардлагагүй.

## Шалгасан зүйл

24 C++ snippet-ийг g++ -std=c++17-аар compile хийж, expected result болон тохирох сэдвүүдэд brute-force/randomized харьцуулалтаар шалгасан. Fenwick, segment tree/lazy tree, binary search, knapsack, LIS, KMP, LCA, Dijkstra зэрэгт naive/reference хариутай тулгасан.

Бодит Chromium дээр 24 хичээлийн хайлт, category filter, дэлгэрэнгүй 10 хэсэг, бүх MathJax SVG formulas, direct link/reload, Back/Forward, rapid switching, 390px mobile layout, renderer failure fallback-ийг шалгасан. Хуучин бодлогын жагсаалт guest горимд ажиллаж байгааг мөн шалгасан. Live Supabase account эсвэл GitHub deployment дээр энэ шинэчлэлтийг шалгаж байршуулсан гэж үзэхгүй.
