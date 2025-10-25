# 02 – Elektromanyetik Fizik Vitrini

Bu örnek, elektromanyetik süreçlerde fizik listelerini nasıl özelleştireceğini, makrolar üzerinden birincil parçacık kaynağını (GPS) nasıl yöneteceğini ve katmanlı geometride doz profilini nasıl toplayacağını gösterir.

## Derleme

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0
cmake --build build
```

## Örnek Çalıştırmalar

```sh
./build/emShowcase macros/run_electron.mac
./build/emShowcase macros/run_gamma.mac
```

- `run_electron.mac`: 80 MeV elektron demetiyle katmanlarda enerji kaybını incele.
- `run_gamma.mac`: 5 MeV gama demetiyle farklı etkileşimleri gözlemle.

## Öğrenme Hedefleri

- Referans fizik listeleri (`FTFP_BERT`, `FTFP_BERT_EMZ`, `QGSP_BERT_HP`) arasında geçiş; hangi enerji aralığında hangisinin uygun olduğunu kavra.
- `G4GeneralParticleSource` parametrelerini tamamen makro komutlarıyla yönet; kodu değiştirmeden deney senaryosu oluştur.
- `G4MultiFunctionalDetector` ve `G4PSEnergyDeposit`, `G4PSDoseDeposit` primitifleriyle katman bazlı doz ölçümü yap.
- EM süreçleri için biasing/ayar kontrollerini deneyerek simülasyon süresini veya doğruluğunu nasıl etkilediğini gözlemle.

## Genişletme Fikirleri

- Şema üzerine ince bir kurşun (Pb) tabaka ekleyip kalkanlama etkisini karşılaştır.
- Çalışma anında `UseEMPhysics` bayrağını değiştirip sonuçlardaki farkı raporla.
- Her bölge için üretim kesimlerini (`production cuts`) ayarlayarak parçacık menzillerinin sonuçlara etkisini incele.

Bu modül, elektromanyetik süreçlerin doğru modellenmesi için gereken araçları tanıtır. Kod içi Türkçe yorumlar, hangi sınıfın hangi fiziksel büyüklüğü temsil ettiğini açıklar.
