# Think CP — эхнээс нь ажиллуулах

Энэ хувилбар 24 бодлого, 5 багц, бодлого бүрд 3 hint, тэмдэглэл, progress хадгалалттай. Халаалтын зарим бодлого 1300-аас хялбар. Багцууд нь сургалтын баримжаа; албан CF rating биш. 50–80 бодлоготой сан болгох ажил дараагийн өргөтгөл.

GitHub холболт бичих үйлдлийг 403 алдаагаар татгалзсан тул энэ багц repository-д автоматаар ороогүй. ZIP-ийг задлаад repository-ийн **Add file → Upload files** хэсэгт файлууд болон `supabase` хавтсыг оруулж **Commit changes** дар. `index.html` нь repository-ийн үндсэн түвшинд байх ёстой; бүх файлыг нэмэлт `think-cp` хавтас дотор бүү оруул.

JavaScript syntax, бодлогын сангийн бүтэц, hint/төлөв/тэмдэглэл/шүүлтүүр/хадгалалт/сэргээх логикийг автомат шалгалтаар шалгасан. Бодит browser-ийн харагдац болон бодит Supabase account/RLS шалгалт энэ орчинд хийгдээгүй. Нийтлэсний дараа утас болон компьютер дээр нэг бодлого туршаарай.

## 1. GitHub Pages нээх

1. https://github.com/erdene1231/think-cp/settings/pages руу ор.
2. **Build and deployment → Source → Deploy from a branch** сонго.
3. **Branch → main**, хажуугийн folder → **/ (root)** сонго.
4. **Save** дар.
5. GitHub-ийн **Actions** хэсэгт Pages build and deployment дуусахыг хүлээ. Settings → Pages дээр **Visit site** гарна.
6. Сайт: https://erdene1231.github.io/think-cp/ . Нийтлэлт дуусаагүй байхад 404 гарч болно.

Repository бол код хадгалдаг газар. Pages бол тэр кодоор сайтаа интернэтэд үзүүлэх үйлчилгээ. Сурагчид сайт ашиглахын тулд GitHub account үүсгэх шаардлагагүй. Файлаа main дээр шинэчилбэл Pages дахин нийтэлнэ.

## 2. Одоо шууд ажиллах зүйлс

- Багц, эх сурвалж, төлөвөөр шүүх, нэрээр хайх.
- Эх бодлого руу очих; submit-аа Codeforces/CSES дээр хийх.
- “Оролдож байгаа”, “Бодсон” төлөвийг өөрөө тэмдэглэх.
- Hint-ийг нэг нэгээр нээх; “Бодсон” болоход сэдэв болон эргэцүүлэх асуулт харах.
- Тэмдэглэл болон progress тухайн browser-ийн local storage-д хадгалагдах.
- **Progress татах**-аар JSON нөөц авах; **Progress сэргээх**-ээр сэргээх. Browser-ийн өгөгдлийг устгавал дотоод progress арилна.

Hint ба сэдвийг интерфэйс дээр л нуусан. JSON болон source code-оос унших боломжтой. Энэ сайт шалгалтын хамгаалалттай орчин биш.

## 3. Жинхэнэ account идэвхжүүлэх

Account-ын код бэлэн боловч Supabase project холбох хүртэл зочин горим ажиллана. Онлайн хадгалалт одоогоор идэвхтэй гэж ойлгож болохгүй.

1. https://supabase.com/dashboard дээр account үүсгэж **New project** дар. Project-оо үүсгээд database-ийн password-оо өөртөө хадгал.
2. Project-ийн **SQL Editor → New query** руу ор. Repository дахь `supabase/schema.sql`-ийн бүх агуулгыг хуулж **Run** дар. Энэ SQL-ийг нэг удаа ажиллуулна.
3. **Authentication → URL Configuration** хэсэгт **Site URL**-ийг `https://erdene1231.github.io/think-cp/` болго. **Redirect URLs**-д мөн энэ яг URL-ийг нэм.
4. Email/password нэвтрэлтийг идэвхтэй байлга. Email баталгаажуулалт ашиглавал хэрэглэгч бүртгүүлсний дараа inbox дахь холбоосоо дарж, сайт руу буцаж нэвтэрнэ. Өөрийн домэйнтэй SMTP тохируулга нь жинхэнэ сурагчдыг урихаас өмнө хэрэгтэй байж болно; Supabase-ийн email хязгаар, SMTP зааврыг шалга.
5. Project-ийн **Connect** эсвэл **Settings → API** хэсгээс **Project URL** болон **publishable key** (хуучин project дээр `anon` public key) ав.
6. GitHub дээр `config.js` файлыг нээгээд харандаа **Edit** дар. Хоёр хоосон утгыг солиод **Commit changes** дар:

```js
window.THINK_CP_CONFIG = {
  supabaseUrl: 'https://ТАНЫ-PROJECT.supabase.co',
  supabaseKey: 'ТАНЫ-PUBLISHABLE-KEY'
};
```

**Нийтийн publishable/anon key** нь browser дотор ашиглах зориулалттай. `service_role`, `secret key`, database password-оо энэ файлд хэзээ ч оруулахгүй. Schema дахь RLS нь сурагч зөвхөн өөрийн progress-ийг уншиж, бичих эрхтэй болгоно.

7. Pages шинэчлэгдсэний дараа **Нэвтрэх → Бүртгүүлэх** ашигла. Email-ээ баталгаажуулж нэвтэр. Нэг бодлогын төлөв өөрчилж, өөр browser-оос адил account-аар орж хадгалалтаа шалга.
8. Хоёр тусдаа test account-аар шалга: эхний account-ын progress хоёр дахь account-д харагдах ёсгүй. Онлайн account ба RLS-ийг бодит project дээр холбохоос өмнө энэ орчинд шалгаагүй.

Зочин progress-ийг account руу автоматаар хуулахгүй. Нэвтрэхээсээ өмнө progress татаж аваад, нэвтэрсний дараа сэргээвэл account руу хадгална. Сэргээх нь файлд орсон бодлогын одоогийн төлөвийг солино. Хадгалалт тасарвал дотоод хуулбар, pending өөрчлөлт хадгалагдана; интернэт орж ирэхэд эсвэл account цэсний дахин оролдох товчоор илгээнэ. Нэг бодлогыг олон төхөөрөмжөөс зэрэг өөрчилбөл серверт сүүлд хүрсэн өөрчлөлт тэр мөрийг бүхэлд нь солино.

## 4. Бодлого нэмэх

GitHub дээр `problems.json → Edit` нээ. `problems` жагсаалтанд дараах хэлбэрийн нэг объект нэм. Сүүлийн объектын араас таслал нэмэхийг мартуузай; JSON дотор comment бичихгүй.

```json
{
  "id": "cf-CONTEST-INDEX",
  "pack": "discover",
  "title": "Бодлогын албан нэр",
  "source": "Codeforces",
  "ref": "CONTEST/INDEX",
  "level": "Үндсэн дасгал",
  "url": "https://codeforces.com/problemset/problem/CONTEST/INDEX",
  "hints": ["Юуг ажиглах вэ?", "Нэг алхам ойртуул", "Гол санаа"],
  "tags": ["Бодсоны дараа харагдах сэдэв"],
  "lesson": "Энэ санаагаа яаж батлах вэ?"
}
```

ID давтагдахгүй, `pack` нь `packs` дахь ID-тай таарна. 3 hint бич. Өгүүлбэрийг хуулж оруулахгүй; албан бодлого руу холбоно. Шинэ hint бүрийг бодлогын нөхцөлтэй тулгаж шалга.

## Албан эх сурвалж

- GitHub Pages: https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site
- Supabase Auth: https://supabase.com/docs/guides/auth
- RLS: https://supabase.com/docs/guides/database/postgres/row-level-security
- Email/SMTP: https://supabase.com/docs/guides/auth/auth-smtp
- CSES: https://cses.fi/problemset/
- EGOI 2023: https://egoi23.se/competition/tasks (монгол өгүүлбэр, testdata, solution, Kattis холбоосууд энд бий).
