# Following, Admin болон English hint шинэчлэлт

## Суулгах дараалал

1. Өмнөх `supabase/003-profiles-friends.sql` migration ажилласан байх ёстой. Supabase → Authentication → Users хэсэгт `bayarjargalmunkherdene12@gmail.com` account бүртгэлтэй эсэхийг шалгана.
2. Supabase → SQL Editor → New query нээгээд `supabase/004-following-admin.sql` файлын **бүх агуулгыг** хуулж Run дарна. Бодлогын анхны өгөгдөл энэ файлд багтсан. Хэрэв admin email олдохгүй бол migration бүхэлдээ буцаагдана; account бүртгүүлсний дараа дахин ажиллуулна.
3. ZIP-ийн дараах 8 файлыг GitHub repository-ийн үндсэн хавтсанд нэмэх/солих: `index.html`, `styles.css`, `app.js`, `social.js`, `catalog.js`, `problems.json`, `admin.js`, `problem-store.js`. Commit хийгээд GitHub Pages шинэчлэгдэхийг хүлээнэ. **Одоогийн `config.js`-ээ хэвээр үлдээнэ.**
4. Admin account-аар дахин нэвтэрнэ. Навигацад Admin хэсэг гарна. Бусад хэрэглэгчид энэ хэсэг харагдахгүй.

SQL файлыг GitHub-д байрлуулах нь Supabase дээр migration ажиллуулахгүй. Энэ багц өмнөх account/profile/friends шинэчлэлтийн дээр суух зориулалттай; `accounts.js`, `community.js`, `progress.js` өөрчлөгдөөгүй. Өмнөх шинэчлэлтийг суулгаагүй бол эхлээд UPDATE-ACCOUNTS.md зааврыг дагана.

## Following

- Хэрэглэгчийн profile дээр Follow хийх / Follow болих товч байна.
- Following tab дээр өөрийн дагаж буй хүмүүсийг харж, profile-ийг нь нээх эсвэл unfollow хийж болно.
- Найзын хүсэлт илгээсэн хүн хүлээн авагчийг автоматаар follow хийнэ. Зөвшөөрөхөд хоёр тал бие биеэ follow хийнэ.
- Өмнөх pending хүсэлт болон accepted friendship-үүдийг migration автоматаар нэмнэ.
- Хүсэлт цуцлах, татгалзах, найзаас хасах нь following-ийг устгахгүй. Follow болихыг тусад нь сонгоно.

## Admin

Эхний migration дээр заасан email-ийн account-ыг UUID-аар холбоно. Дараагийн эрхийн шалгалт UUID-д тулгуурлана; browser дахь email, user metadata өөрчилж admin болох боломжгүй. Migration дахин ажиллуулахад өөр account руу admin эрх шилжихгүй. Admin-ийн хүсэлт бүрийг database дахин шалгана.

Admin хэсгээс:

- Бодлого нэмэх, нэр, холбоос, эх сурвалж, rating, English tags, priority, тайлбар засах.
- Монгол болон English хэлний 3 hint-ийг тус тус засах.
- Бодлогыг жагсаалтаас хасах, хассан бодлогыг сэргээх.

Хасах нь archive үйлдэл: хэрэглэгчдийн хувийн progress, notes хадгалагдана. Хассан бодлого public profile болон leaderboard-ийн идэвхтэй бодлогын тоонд орохгүй; сэргээхэд өмнөх progress буцаж харагдана. Нэг бодлогыг хоёр tab-аас зэрэг засахад хуучин revision шинэ өөрчлөлтийг дарж бичихгүй; дахин ачаалаад засна.

Admin өөрчлөлт Supabase-д хадгалагдана. Хэрэглэгч сайт нээхэд, эсвэл “Санг шинэчлэх” дарахад шинэ catalog авна. Admin өөрчлөлт бүрийн дараа өөрийн дэлгэцийн catalog шинэчлэгдэнэ. JSON нь анхны/offline fallback; admin өөрчлөлт бүрийг GitHub-д дахин оруулах шаардлагагүй.

## Бодлогын ID ба English hint

- Бодлого бүр байнгын тоон ID-тай: #001, #002 гэх мэт. Анхны 24 бодлого → дараагийн нэмэгдсэн багц → энэ шинэчлэлтийн бодлогын дарааллаар дугаарласан. Нийт 85.
- Шинээр нэмэхэд дараагийн дугаар автоматаар олгогдоно. Засах, эрэмбэлэх, archive/restore хийхэд дугаар өөрчлөгдөхгүй, дахин ашиглагдахгүй. Sequence-ийн дугаар алгасах боломжтой.
- Өмнөх internal ID-г хэвээр хадгалсан тул progress холбоос тасрахгүй. Тоон ID-аар хайх, нэмсэн дарааллаар эрэмбэлэх боломжтой.
- Hint хэсэгт Монгол / English сонголт нэмсэн. 85 бодлогын 255 hint English хувилбартай. Хэл солих нь нээсэн hint-ийн тоог нэмэхгүй; нуух/харуулах ажиллана. Сонгосон хэл browser-т хадгалагдана.
- Өмнөх CSES 1097 холбоосын алдааг зассан: 1097 нь Removal Game, DP hint болон rating-ийг тохируулсан. Apple Division нь CSES 1623 холбоостой тусдаа #085 бодлого болсон. Хуучин cses-1097 progress тухайн ID дээрээ хадгалагдана.

Migration дахин ажиллуулахад admin-аар зассан бодлого, revision, archive төлөвийг seed дарахгүй. 004-ийн дараа хуучин 003 migration-ийг дахин ажиллуулахгүй; шаардлагатай бол 004-ийг дахин ажиллуулна.

## Шалгалт

PostgreSQL-compatible PGlite дээр migrations, RLS/RPC эрх, admin binding, auto-follow, дугаарын дараалал, revision conflict, archive/restore, progress хадгалалт шалгасан. Жинхэнэ Chromium дээр mock Supabase ашиглаж admin CRUD, following, English hint, profile/avatar, recovery, friends, logout болон 390px mobile layout шалгасан.

Бодит Supabase болон GitHub Pages дээр энэ багцыг хараахан суулгаагүй. Суулгасны дараа admin ба энгийн account-аар нэвтэрч эрхийн ялгаа, шинэ бодлого нэмэх/засах/хасах/сэргээх, найзын хүсэлтээр following нэмэгдэх, English hint болон хоёр browser-ийн catalog refresh-ийг шалгана.
