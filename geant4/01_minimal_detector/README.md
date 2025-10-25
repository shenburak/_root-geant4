# 01 – Minimal Dedektör ve Skorlama Hacmi

Bu küçük Geant4 uygulamasıyla temel kullanıcı sınıflarını tanıyacaksın: dedektör inşası, birincil ışın üretimi, fizik listesi seçimi ve run/action sınıflarının yapılandırılması. Sonuçta bir skorlama hacmine gelen enerji kaybını kaydedip özet istatistikleri yazdırıyoruz.

## Derleme

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0
cmake --build build
```

## Çalıştırma

```sh
./build/minimalDetector macros/init_vis.mac
./build/minimalDetector macros/run.mac
```

- `init_vis.mac`: Geometriyi görsel olarak incelemek için UI açar, eksenler ve ışın parametreleri yüklü gelir.
- `run.mac`: Batch modda 1000 olay üretir, istatistikleri konsola ve `.root` dosyasına kaydeder.

## Temel Dosyalar

- `src/DetectorConstruction.cc`: Dünya hacmi, silikon blok ve skorlama hacmi tanımları.
- `src/PrimaryGeneratorAction.cc`: Parçacık tabancasını konfigüre eder (enerji, yön, konum).
- `src/RunAction.cc`, `src/EventAction.cc`: Enerji birikimini toplayıp run sonunda raporlar.
- `macros/`: Görselleştirme (`init_vis.mac`) ve batch çalışma (`run.mac`) için komut dosyaları.

## Deney Fikirleri

- `macros/run.mac` içindeki `/gun/energy` değerini değiştir ve çıktıda enerji ortalamasının nasıl değiştiğini gözlemle.
- Görselleştirme modunda `/vis/viewer/` komutlarını kullanarak kamera açısını değiştir; dedektörü üç boyutlu incele.
- Adım adım (stepping) çıktılarını görmek için `SteppingAction` sınıfında log seviyesini artır veya yeni mesajlar ekle; hata ayıklarken çok faydalıdır.

Bu örnek temelini pekiştirdikten sonra, sonraki modüllerde daha karmaşık geometri ve fizik senaryolarına hazır olacaksın.
