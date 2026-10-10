# Бүтэн C++17 жишээнүүд

43 tutorial тус бүрийн input уншдаг, шууд compile хийх program энд байна.
Website-ийн 13-р хэсэгт input-ийн дүрэм, жишээ input/output, бүтэн program нь бий.
`samples.json`-д мөн бүх жишээ, хоёр хэлний input contract хадгалсан.

Жишээ нь segment tree:

```bash
g++ -std=c++17 -O2 segment-tree.cpp -o segment-tree
./segment-tree
```

Дараах input-ийг оруулна:

```text
4 3
2 1 3 4
sum 1 3
set 2 8
sum 1 3
```

Output:

```text
8
13
```

`set` нь утгыг сольдог. Fenwick-ийн `add` нь нэмдэг. Заагийн дүрэм,
index-ийг tutorial бүрээс шалга: бүх program нэг input format-тай биш.

| № | Хичээл | Program |
|---|---|---|
| 1 | Time complexity — код хэр их ажил хийх вэ? | [complexity.cpp](complexity.cpp) |
| 2 | Brute force — бүх боломжийг шалгах | [brute-force.cpp](brute-force.cpp) |
| 3 | Sorting — эрэмбэлэх | [sorting.cpp](sorting.cpp) |
| 4 | Recursion — өөрийгөө дуудах function | [recursion.cpp](recursion.cpp) |
| 5 | Stack ба queue | [stack-queue.cpp](stack-queue.cpp) |
| 6 | Set ба map — утга ба давтамж | [set-map.cpp](set-map.cpp) |
| 7 | Prefix sum — хэсгийн нийлбэр | [prefix-sums.cpp](prefix-sums.cpp) |
| 8 | Difference array — олон range нэмэлт | [difference-array.cpp](difference-array.cpp) |
| 9 | 2D prefix sum — grid-ийн хэсгийн нийлбэр | [prefix-sums-2d.cpp](prefix-sums-2d.cpp) |
| 10 | Binary search — sorted array дотор хайх | [binary-search.cpp](binary-search.cpp) |
| 11 | Two pointers ба sliding window | [two-pointers.cpp](two-pointers.cpp) |
| 12 | Bit operations — binary ба жижиг олонлог | [bit-operations.cpp](bit-operations.cpp) |
| 13 | GCD — хамгийн их ерөнхий хуваагч | [gcd.cpp](gcd.cpp) |
| 14 | Fast power — хурдан зэрэгт дэвшүүлэх | [fast-power.cpp](fast-power.cpp) |
| 15 | Sieve — олон анхны тоо олох | [sieve.cpp](sieve.cpp) |
| 16 | Graph-ийн суурь ба adjacency list | [graph-basics.cpp](graph-basics.cpp) |
| 17 | BFS — хамгийн цөөн алхмаар хүрэх | [bfs.cpp](bfs.cpp) |
| 18 | DFS — нэг салаагаар гүн рүү орох | [dfs.cpp](dfs.cpp) |
| 19 | Flood fill — grid доторх холбоотой хэсэг | [flood-fill.cpp](flood-fill.cpp) |
| 20 | Greedy — зөв сонголтыг алхам бүрт хийх | [greedy.cpp](greedy.cpp) |
| 21 | Binary search on answer | [binary-search-answer.cpp](binary-search-answer.cpp) |
| 22 | Coordinate compression — утгыг index болгох | [hash-compression.cpp](hash-compression.cpp) |
| 23 | Tree-ийн суурь — parent, depth, subtree | [tree-basics.cpp](tree-basics.cpp) |
| 24 | DP-ийн эхлэл — хариунуудаа хадгалах | [dynamic-programming.cpp](dynamic-programming.cpp) |
| 25 | Grid DP — замын тоо | [grid-dp.cpp](grid-dp.cpp) |
| 26 | 0/1 knapsack — авах эсвэл авахгүй | [knapsack.cpp](knapsack.cpp) |
| 27 | LIS — өсөх subsequence | [lis.cpp](lis.cpp) |
| 28 | Monotonic stack — дараагийн том утга | [monotonic-stack.cpp](monotonic-stack.cpp) |
| 29 | DSU — бүлгүүдийг нэгтгэх | [dsu.cpp](dsu.cpp) |
| 30 | Kruskal — хамгийн хямд холбоосууд | [kruskal.cpp](kruskal.cpp) |
| 31 | Priority queue — хамгийн бага утгыг түрүүлж авах | [priority-queue.cpp](priority-queue.cpp) |
| 32 | Dijkstra — жинтэй graph-ийн богино зам | [dijkstra.cpp](dijkstra.cpp) |
| 33 | Floyd–Warshall — бүх хосын богино зам | [floyd-warshall.cpp](floyd-warshall.cpp) |
| 34 | Topological sort — dependency-ийн дараалал | [topological-sort.cpp](topological-sort.cpp) |
| 35 | Fenwick tree — өөрчлөгддөг prefix sum | [fenwick-tree.cpp](fenwick-tree.cpp) |
| 36 | Recursive segment tree — хэсгийг хувааж хадгалах | [segment-tree.cpp](segment-tree.cpp) |
| 37 | Sparse table — static range minimum | [sparse-table.cpp](sparse-table.cpp) |
| 38 | Prime factorization — анхны үржигдэхүүнд задлах | [number-theory.cpp](number-theory.cpp) |
| 39 | Combinatorics — сонголтын тоо ба Pascal DP | [combinatorics.cpp](combinatorics.cpp) |
| 40 | KMP — string дотор pattern хайх | [kmp.cpp](kmp.cpp) |
| 41 | LCA — хоёр node-ийн нийтлэг ancestor | [lca.cpp](lca.cpp) |
| 42 | Bitmask DP — сонгосон олонлогоор state үүсгэх | [bitmask-dp.cpp](bitmask-dp.cpp) |
| 43 | Lazy segment tree — range нэмэлтийг хойшлуулах | [lazy-segment-tree.cpp](lazy-segment-tree.cpp) |
