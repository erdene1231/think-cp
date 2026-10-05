# Think CP account шинэчлэл

## Шинэ боломжууд

- Email-д ирсэн recovery код → код баталгаажуулах → шинэ password давтаж оруулах.
- Profile зураг (JPG/PNG/WebP, 2 MB хүртэл), овог нэр, сургууль, username.
- Зургийг browser дээр дөрвөлжин болгон тайрч, хамгийн ихдээ 512×512 WebP болгож хадгална. Зураг солих/устгах боломжтой.
- Бүх бүртгэлтэй хэрэглэгчдийг бодсон бодлогын тоогоор жагсаана. Ижил тоо = ижил rank. Username тохируулаагүй account ч жагсаалтад орно.
- Username, овог нэр, сургуулиар хэрэглэгч хайна. 50 хэрэглэгчээр pagination хийнэ.
- Хэрэглэгчийн profile дээр бодсон/бодож байгаа бодлогууд, бодсон хувь, rank харагдана. Бодлого дээр дарж нээж болно.
- Friends: хүсэлт илгээх, зөвшөөрөх/татгалзах, илгээсэн хүсэлт цуцлах, найзаас хасах. Ирсэн/илгээсэн хүсэлт, найзууд тусдаа жагсаалттай.
- Бодлогын “Хэн бодсон бэ?” жагсаалтын username дээр дарж profile нээнэ.
- Дээд navigation-аас Бодлогууд, Хэрэглэгчид, Friends хэсэг рүү очно.

Profile зураг, овог нэр, сургууль, username, бодсон/бодож байгаа бодлогууд нийтэд харагдана. Email, хувийн тэмдэглэл, нээсэн hint-ийн тоо бусдад харагдахгүй. Бодсон төлөвийг хэрэглэгч өөрөө тэмдэглэнэ; Codeforces submit-ийг автоматаар баталгаажуулахгүй.

## 1. Supabase SQL ажиллуулах

Одоогийн project дээр `schema.sql` болон `002-usernames-solvers.sql` өмнө нь ажилласан байх ёстой.

1. Supabase project → SQL Editor → New query.
2. Багц дахь `supabase/003-profiles-friends.sql`-ийн **бүх агуулгыг** хуулж Run дар.
3. Энэ migration хуучин account/progress-ийг устгахгүй. Хуучин account-уудын дутуу profile-ийг нөхөж, шинэ account-д profile автоматаар үүсгэх trigger, friends хүсэлтүүд, public profile/ranking RPC, зураг хадгалах `think-cp-avatars` bucket болон эрхүүдийг үүсгэнэ. Дахин ажиллуулж болно.

Leaderboard нь одоогийн 84 бодлогын ID-г `problem_catalog` хүснэгттэй тулгаж тоолдог. Шинэ бодлого нэмэхдээ JSON-оос гадна SQL Editor-т дараах байдлаар ID-г нэм:

```sql
insert into public.problem_catalog(problem_id)
values ('cf-NEW-ID') on conflict(problem_id) do nothing;
```

## 2. Password сэргээх email тохируулах

1. Authentication-ийн Email Templates дотор **Reset Password** template-ийг нээ.
2. Subject-ийг `Think CP — Нууц үг сэргээх код` болго.
3. Email body-г `supabase/templates/reset-password.html` файлын агуулгаар сольж Save дар. `{{ .Token }}`-ийг яг хэвээр үлдээнэ. Энэ нь Supabase-ийн өөрөө үүсгэдэг нэг удаагийн код; өөрийн random код эсвэл magic-link login ашиглахгүй.
4. Authentication → URL Configuration дахь Site URL болон Redirect URLs-д `https://erdene1231.github.io/think-cp/` байгаа эсэхийг шалга.
5. Бүх сурагчдад recovery email илгээхийн тулд **Custom SMTP** тохируулсан байх хэрэгтэй. Supabase-ийн default mail service нь project-ийн зөвшөөрөгдсөн team email-ууд руу л илгээх хязгаартай. Өмнө нь custom SMTP тохируулсан бол хэвээр ашиглана. Шинээр тохируулах бол өөрийн email provider-ийн host, port, username, password, sender email/name-ийг Supabase-ийн Custom SMTP хэсэгт оруул. SMTP password-ийг сайтад/config.js-д оруулахгүй.

Хэрэглэгч: Account → Нууц үг мартсан / сэргээх → Email → код → шинэ password.
Кодын урт project-ийн Auth тохиргооноос хамаарна; email дээр ирсэн кодоо тэр чигээр нь оруулна. Код expired/буруу бол шинэ код авна. Дахин илгээхэд нэг минутын UI хүлээлттэй; Supabase-ийн server rate limit мөн үйлчилнэ.

## 3. GitHub файлууд шинэчлэх

ZIP-ийг задлаад repository-ийн үндсэн хавтаст дараах **5 код файлыг** Upload files-аар оруул:

- index.html
- styles.css
- app.js
- accounts.js (шинэ)
- social.js (шинэ)

`supabase/003-profiles-friends.sql`, `supabase/templates/reset-password.html`, `UPDATE-ACCOUNTS.md`-ийг мөн repository-д хадгалж болно. GitHub дээр SQL файл оруулах нь SQL-ийг ажиллуулахгүй; дээрх SQL Editor алхам заавал хэрэгтэй.

`config.js`, `problems.json`, `progress.js`, `community.js`, `catalog.js`-ийг өөрчлөх шаардлагагүй. Шинэ account код нь өмнөх каталог, cache болон hint нуух засваруудыг хадгалсан.

Одоогийн GitHub холболт write үйлдэлд 403 буцаадаг тул энэ багц автоматаар нийтлэгдээгүй. Commit хийж Pages build дууссаны дараа refresh хий.

## 4. Бодит project дээр турших

1. Хоёр test account-аар зураг/овог нэр/сургууль хадгал; өөр browser-аас шинэчлэгдсэнийг хар.
2. Бодсон болон бодож байгаа бодлого тэмдэглэж, public profile/жагсаалтыг шинэчилж шалга.
3. Нэг account-аас нөгөө рүү найзын хүсэлт илгээж, нөгөө талд ирснийг харж зөвшөөр; хоёр талд найз болж харагдана.
4. Account-аас гараад Password сэргээх ашигла. Бодит email кодоор password шинэчилж, шинэ password-аар нэвтэр.
5. Public profile-д email, хувийн тэмдэглэл, hint-ийн тоо харагдахгүй байхыг шалга.

## Хийгдсэн шалгалт

- PostgreSQL хөдөлгүүр (PGlite): migration хоёр удаа ажиллах, хуучин/шинэ account profile, catalog-той тулгасан count/rank, search/pagination, public projection, own-row RLS, friends үйлдлийн эрх/төлөв, өөр хэрэглэгчийн avatar хавтас руу бичихгүй байх.
- API helpers: талбарын урт/username, avatar MIME/хэмжээ/path, recovery OTP type, буруу код, password confirmation, account солигдсон үед password өөрчлөхгүй байх, avatar cleanup.
- Жинхэнэ Chromium + mock Supabase: profile засвар, зураг resize/upload/delete, duplicate username, profile/leaderboard, friends request/cancel/accept, recovery буруу/зөв код/password, hint regression, logout isolation, 390 px mobile layout.
- HTML/JS IDs болон JavaScript syntax шалгасан. Утасны харагдацыг screenshot-аар нягталсан.

Бодит Supabase project-ийн admin тохиргоо, бодит Storage upload, email хүргэлтийг эндээс өөрчлөөгүй/туршаагүй. Дээрх SQL, email template, SMTP тохиргоо нь нийтлэхэд шаардлагатай.

## Албан заавар

- https://supabase.com/docs/reference/javascript/auth-resetpasswordforemail
- https://supabase.com/docs/reference/javascript/auth-verifyotp
- https://supabase.com/docs/guides/auth/auth-email-templates
- https://supabase.com/docs/guides/auth/auth-smtp
- https://supabase.com/docs/guides/storage/security/access-control
