# ROOT Modül Yol Haritası

ROOT tarafındaki tüm örnekleri burada bulacaksın. Klasörlerin numaralı olması takip etmeni kolaylaştırır; sırasıyla ilerlediğinde her adım bir öncekinin üzerine yeni bir kavram ekler. Açıklamalar Türkçe, kodlar İngilizce isimlendirilmiş ama bol yorum içeriyor.

## İçerik Listesi

1. `01_basic_histogram` – Histogram çizimi, kanvas yönetimi ve `.root` dosyasına kayıt ile hızlı başlangıç.
2. `02_ttree_analysis` – CSV gibi yapılandırılmış verilerin `TTree`’ye aktarılması ve `RDataFrame` ile analiz.
3. `03_pyroot_fitting` – PyROOT kullanarak model uydurma (fitting), hata analizi ve görselleştirme.
4. `04_root_macros` – Parametrelenebilir ROOT makrolarıyla toplu (batch) çalışma ve üretkenlik ipuçları.

## Başlamadan Önce Adımlar

- `root-config --version` komutuyla kurduğun sürümün beklediğin sürüm olduğunu doğrula. Farklıysa PATH ayarını gözden geçir.
- Cling hızlı testi: `root -l -q 'std::cout<<"ROOT hazır"<<std::endl;'`. Bu komut çalışmazsa derleyici ayarların eksik olabilir.
- PyROOT testi: `python3 -c 'import ROOT; print(ROOT.__version__)'`. Bilimsel hesaplamalarda Python entegrasyonu kritik, bu adımı atlama.

## Derleme ve Çalıştırma Düzeni

- Her C++ örneğinde `root-config` bayraklarını kullanan bir `Makefile` var; böylece kendi derleyici parametrelerini hatırlamak zorunda değilsin.
- Terminalde `make` dediğinde proje derlenir; ardından örneğin `./basic_histogram` komutuyla uygulamayı başlat.
- Kaynak temizliği: `make clean` histogram dosyalarını, ikili dosyayı ve geçici çıktıları siler.

## Kapsamlı Öğrenme İçin Ek Öneriler

- Histogram projesinde kutu (bin) sayısını, eksen etiketlerini değiştir ve çıktının iş gereksinimine (rapor, sunum vb.) uygun görünüp görünmediğini değerlendir.
- Histogram örneğini PyROOT’a çevirerek kod tekrarını azalt, böylece hızlı prototip çıkar. Entegrasyon projelerinde Python hız sağlar.
- TTree projesine `RDataFrame` filtreleri ekle, `Snapshot` ile farklı alt veri setleri oluştur. Bu yaklaşım gerçek veri analizi süreçlerini taklit eder.
- Fit örneğinde `ROOT::Math::MinimizerOptions::SetDefaultTolerance()` ayarıyla optimizasyon hassasiyetinin sonuçlara etkisini incele ve raporla.

Her klasördeki README sana bilimsel arka planı, iş değerini ve tekrar edilebilir adımları verir. Notlarını bu dosyalara eklemek, ileride yapılacak projelerde referans sağlar.
