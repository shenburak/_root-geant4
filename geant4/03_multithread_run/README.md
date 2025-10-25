# 03 – Çok İş Parçacıklı (MT) Çalıştırma ve Anlık Analiz

Bu örnek, Geant4’ün çok iş parçacıklı koşu yöneticisini (`G4MTRunManager`) kullanarak eşzamanlı histogram doldurma ve ntuple yazma süreçlerini nasıl yöneteceğini gösterir. Hedefimiz özelleştirilebilir bir parçacık demetiyle vurulan basit bir kalorimetre ve katman bazlı enerji istatistikleri.

## Derleme

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0 -DGEANT4_BUILD_MULTITHREADED=ON
cmake --build build
```

## Çalıştırma

```sh
OMP_NUM_THREADS=4 ./build/mtCalorimeter macros/batch.mac
```

Çıktılar `output/mt_run.root` dosyasına yazılır ve her katman için ayrı enerji histogramları içerir. `OMP_NUM_THREADS` değerini sistemindeki çekirdek sayısına göre ayarlayabilirsin.

## Öne Çıkanlar

- Thread-local (iş parçacığına özel) toplama yapan `G4MTRunManager` kullanımı.
- `G4AnalysisManager` ile thread-safe histogram ve ntuple üretimi; ROOT arka planı sayesinde çıktı formatı uyumlu.
- Komut makroları aracılığıyla olay sayısını, ışın enerjisini ve diğer parametreleri kodu değiştirmeden kontrol etme.
- `ActionInitialization::BuildForMaster` ve `Build` içinde ana iş parçacığı ile çalışan iş parçacıklarının farklı başlangıç görevlerini yapması.

## Sonraki Adımlar

- İş parçacığı sayısını artırıp çalışma süresindeki ölçeklenmeyi ölç; rapor hazırla.
- Ntuple’a iz uzunluğu (track length) veya parçacık türü gibi yeni sütunlar ekleyerek veri zenginliğini artır.
- `macros/beam.mac` dosyasını değiştirip enerji spektrumu tanımla; klinik proton terapi veya radyasyon test senaryosu simüle et.

Çok çekirdekli simülasyonlar özellikle işletme maliyetlerini düşürmek ve bilimsel doğruluğu korumak için kritik öneme sahiptir. Kod içi Türkçe yorumlar neyin nerede başlatıldığını ayrıntılı açıklar.
