# ROOT & Geant4 Hızlı Başvuru Rehberi

Bu sayfa, çalışırken elinin altında bulunması gereken komutları, kavramları ve “neden böyle yapıyoruz?” sorusunun kısa cevaplarını içerir. Her bölümde teknik adımları, fiziksel yorumu ve iş/tasarım perspektifini bulacaksın.

## Ortam Hazırlığı

- `source /path/to/thisroot.sh` – ROOT ortamını yükler. Böylece `PATH`, `LD_LIBRARY_PATH`, `PYTHONPATH` güncellenir. _Teknik:_ Derleyici gerekli başlıkları görür. _Bilimsel:_ ROOT kütüphaneleri veri analizi için erişilebilir olur. _İş:_ Analiz otomasyonu için CI/CD betiklerinde bu komutu kullan.
- `source /path/to/geant4.sh` – Geant4 veri setlerini ve CMake yapılandırmalarını aktive eder. _Bilimsel:_ Fiziksel süreçlerin referans tabloları (kesitler vb.) yüklenir. _İş:_ Simülasyon sonuçları regülasyon gereksinimlerine uyum sağlar.
- `root-config --features` – ROOT derlenirken hangi özellikle etkinleştirildiğini gösterir (örn. `pyroot`, `opengl`). Gereken özellik yoksa kurulumunu güncelle.
- `geant4-config --help` – Geant4’ün CMake’e sağladığı yol ve bayrakları hatırlatır. Çoklu kurulum varsa doğru yolu seçtiğinden emin ol.
- `echo $G4INSTALL` – Geant4 kurulum kökünü doğrula; paylaşılan klasörlerde yetki sorunu varsa hemen görürsün.

## ROOT Temel Komutları

- Etkileşimli kabuk: `root -l`. `.x macro.C` ile makro çalıştır, `.L library.so` ile paylaşılan kütüphane yükle. _Fizik:_ Hızlı deneysel veri kontrolleri. _İş:_ Sunum öncesi görselleri hızlı üret.
- Derleme bayrakları: `$(shell root-config --cflags --libs)`. Makefile’larda kullan; platform farklarını ROOT senin yerini çözer.
- Histogram yazma örneği: `TH1F hist("h", "Enerji", nbins, xmin, xmax); hist.Fill(value); hist.Write();`. _Bilimsel:_ Enerji spektrumlarının istatistiksel dağılımını incele. _İş:_ Kalite kontrol raporları için.
- Ağaç (TTree) kurulum: `TTree tree("events", "Olay verisi"); tree.Branch("energy", &energy); tree.Fill();`. _Fizik:_ Olay tabanlı veri tutma. _Teknik:_ Sütun bazlı depolama sayesinde hızlı sorgu.
- `ROOT::RDataFrame` ile modern analiz: `ROOT::RDataFrame df("events", "file.root"); auto ortalama = df.Filter("energy>1").Mean("energy");`. _İş:_ Veri pipelines oluşturup tekrar kullanılabilir hale getir.
- PyROOT test: `python3 - <<'PY'` bloğu ile anında `import ROOT` doğrula. _Fizik:_ Jupyter veya hızlı prototipleme için önemli.

## Geant4 Temel Komutları

- Yapılandırma: `cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0`. Sürüm numarasını sistemine göre güncelle. _Teknik:_ Doğru G4 kütüphanelerine bağlanır. _İş:_ Üretim hattında yeniden derleme adımlarını otomatize eder.
- Derleme ve çalışma: `cmake --build build && ./build/exampleApp macros/run.mac`. Makro sayesinde ışın parametreleri koddaki değişikliğe gerek kalmadan ayarlanır.
- Geometri görselleştirme: `/control/execute vis.mac`. _Bilimsel:_ Dedektör düzenini hızlı kontrol et. _İş:_ Paydaşlara sunumda göster.
- Fizik listesi değişimi: `/process/list` ile aktif süreçleri gör. `G4PhysListFactory` üzerinden `FTFP_BERT`, `QGSP_BERT_HP` gibi listeleri seç. _Fizik:_ Doğru enerji aralığında uygun yaklaşımı seçmek hassas sonuçlar verir.
- Parçacık tabancası: `/gun/particle proton`, `/gun/energy 200 MeV`, `/run/beamOn 10`. _Bilimsel:_ Klinik proton terapi senaryosu. _İş:_ Tedavi planı doğrulamaları.

## Entegrasyon İpuçları

- `G4AnalysisManager` kullanarak Geant4’ten ROOT ntuple’larına yaz. `Geant4_USE_GDML=ON` bazı geometri dışa aktarımları için şarttır.
- Yüksek hacimli çıktılar için düz metin yerine `TTree` kullan; depolama alanından tasarruf eder ve RDataFrame ile hızlı okunur.
- Makro dosyaları (`macros/` klasörü) ile deney parametrelerini versiyonla. _İş:_ Deneye ait konfigürasyon izlenebilir olur; denetim süreçlerinde kolaylık.
- Paralel çalışmalar: `G4MTRunManager` + `OMP_NUM_THREADS=8 ./build/app macros/run.mac`. _Bilimsel:_ Monte Carlo istatistiğini kısalan sürede elde et. _İş:_ Hesaplama kaynağından tasarruf.

## Hata Ayıklama ve Kalite Kontrol

- ROOT: `gSystem->StackTrace()` ile çökme anında yığın izini gör. `.ls` ile dosyadaki nesneleri listele. _İpucu:_ Tüm çıktıyı `tee root.log` ile logla.
- Geant4: `G4BACKTRACE=1` ortam değişkeni ile segmentasyon hatalarında fonksiyon çağrılarını görürsün. `G4Exception` mesajlarını okumayı ihmal etme.
- Bellek denetimi: `valgrind --tool=memcheck ./build/app macros/run.mac` → `valgrind.log` dosyasını incele. _İş:_ Medikal veya nükleer tesis denetimlerinde şart.
- `G4EmCalculator`: Durdurma gücü gibi elektromanyetik büyüklükleri hızlıca hesaplayıp simülasyon sonuçlarıyla karşılaştır.

## Çalışırken

- Bu dosyayı açık tut, gerektikçe kişisel notlarını ekle. Kendi deney parametrelerini, tarih ve sonuçlarla beraber kaydedersen ileride rapor hazırlaman çok kolaylaşır.
