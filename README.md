# ROOT & Geant4 İki Günlük Yoğun Kamp Alanı

Bu depo, iki gün sürecek ROOT ve Geant4 eğitimine eksiksiz hazırlık yapabilmen için tasarlandı. Her klasör, bir eğitmen eşliğinde laboratuvarda çalışıyormuşsun gibi seni adım adım yönlendirecek Türkçe rehberler, komut setleri ve örnek projeler içeriyor. Teknik ayrıntıları, fiziksel arka planı ve iş dünyasındaki kullanım senaryolarını birlikte anlatarak konuyu farklı açılardan kavramanı hedefliyoruz.

## Kampı Nasıl Kullanmalısın?

- Aşağıdaki zaman planını takip ederek sırayla her modülü okuman ve denemen önerilir. Her klasörde detaylı bir `README.md`, kaynak kodu, yapı betikleri (`Makefile` veya `CMakeLists.txt`) ve ileri okuma önerileri bulunuyor.
- Bütün örnekler birbirinden bağımsızdır; dilediğin projeyi tek başına derleyip çalıştırabilir, diğerlerini etkilemeden üzerinde değişiklik yapabilirsin.
- Kodlar C++17 standartlarını hedefliyor. Analizi hızlandırmak için bazı bölümlerde ek PyROOT (Python) betikleri var. Kod isimlendirmeleri İngilizce bırakıldı, ancak tüm açıklayıcı yorumlar Türkçe.
- ROOT projeleri `root-config` aracına dayanırken, Geant4 projeleri `CMake` üzerinden `find_package(ROOT)` ve Geant4 yapılandırmalarını kullanır. Her README’de terminalde yazman gereken komutlar net şekilde belirtildi.

## İki Günlük Yol Haritası

### 1. Gün – ROOT Temelleri ve Veri Analizi (5–6 saat)

1. **Ortamı Hazırla ve Test Et** (`root/README.md`): ROOT kurulumu, `root-config`, Cling kabuğu ve PyROOT doğrulamaları. _(30 dk)_
2. **Histogramlar ve Giriş/Çıkış** (`root/01_basic_histogram`): Veri üret, histogram oluştur, dosyaya kaydet ve görselleştir. _(45 dk)_
3. **Yapılandırılmış Veri ve TTrees** (`root/02_ttree_analysis`): CSV’yi `TTree`’ye çevir, `RDataFrame` ile filtreleme yap. _(90 dk)_
4. **PyROOT ile Uyumlu Uydurma (Fitting)** (`root/03_pyroot_fitting`): Model uydur, hata hesapla, görseller üret. _(60 dk)_
5. **ROOT Makroları ve Otomasyon** (`root/04_root_macros`): Parametreli makrolar, toplu çalışma ve çıktı yönetimi. _(60 dk)_

### 2. Gün – Geant4 ve ROOT Entegrasyonu (6–7 saat)

1. **Geant4’e Giriş ve Minimal Dedektör** (`geant4/README.md`, `geant4/01_minimal_detector`): Dedektör bileşenleri, duyarlı hacimler, ilk ışın. _(60 dk)_
2. **Geometri ve Elektromanyetik Fizik** (`geant4/02_electromagnetic_showcase`): Fizik listeleri, GPS ile ışın tanımı, doz profilleri. _(90 dk)_
3. **Çoklu İş Parçacığı ve Analiz** (`geant4/03_multithread_run`): MT çalıştırıcı, `G4AnalysisManager` ile histogramlama. _(90 dk)_
4. **ROOT ↔ Geant4 Veri Köprüsü** (`combined/README.md`, `combined/01_g4_to_root`): Geant4 vuruşlarından ROOT ntuplerine akış, PyROOT analizi. _(90 dk)_

Bu planı istersen değiştirebilir, ilgini çeken başlıkları öne alabilirsin. Her aşamada “Neden önemli?” sorusunu önce bilimsel, sonra mühendislik/iş tarafıyla yanıtlamaya çalıştık.

## Depo Yapısı

- `root/`: ROOT odaklı örnekler, Makefile’lar, PyROOT yardımcıları, veri dosyaları.
- `geant4/`: Geant4 tabanlı dedektör ve fizik çalışmaları, CMake projeleri, makro komutları.
- `combined/`: Geant4 çıktılarını ROOT’ta analiz etmeye yönelik karma projeler.
- `docs/`: Hızlı başvuru dokümanları, sık kullanılan komutlar, hata ayıklama ipuçları.

## Başlamadan Önce Gerekenler

- C++17 destekli ROOT 6.28+ kurulumu (`thisroot.sh` ile ortam değişkenlerini aktifleştir).
- Veri setleri yüklenmiş Geant4 11.x (`geant4.sh` veya `geant4-config --datasets` ile doğrula).
- CMake 3.18+, güncel bir derleyici (clang++ veya g++), Python 3.9+ (PyROOT betikleri için) ve tercihen `virtualenv`.
- İş açısından: Bu teknolojiler yüksek enerjili fizik, medikal görüntüleme, radyasyon dozimetresi ve veri yoğunluklu Ar-Ge projelerinde kullanılıyor. İki günlük hazırlık sonrasında proje teklifleri veya akademik sunumlar için prototip hazırlayabilir hale gelirsin.

## Rehberlik İpuçları

- Her klasördeki `README.md`, “Özet → Kurulum → Çalıştırma → Fiziksel yorum → İş/ürün etkisi → Deneyler” sırasıyla ilerler. Bu sırayı bozma, çünkü anlatı birbirini tamamlıyor.
- `docs/cheatsheets.md` dosyası sık kullanılan komutları ve ortam değişkenlerini Türkçe açıklamalarla listeler. Terminalde takıldığında ilk bakacağın yer burası olsun.
- Geant4 projelerini çalıştırmadan önce `cmake -S . -B build` ve ardından `cmake --build build` komutlarını uygula. ROOT projeleri için `make` yeterli.
- Her modülün sonunda “Kendini test et” başlıklı bir bölüm var; bu soruları yanıtladığında dersi sindirdiğinden emin olacaksın.

Keyifli çalışmalar! İhtiyacın olursa GDML içe/dışa aktarma, olay görselleştirme veya grid/batch altyapısına dağıtım gibi ileri konular için de ek başlıklar hazırlayabiliriz.
