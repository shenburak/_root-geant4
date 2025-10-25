# Geant4 Modül Genel Görünümü

Bu bölümde Geant4 ile minimal bir dedektörden başlayıp elektromanyetik fizik senaryolarına, oradan çok iş parçacıklı çalışmalara kadar ilerleyen örnekler bulacaksın. Her proje CMake ile dışarıya (out-of-source) derlenecek şekilde ayarlandı.

## Proje Listesi

1. `01_minimal_detector`: Basit kutu dedektör, duyarlı hacim ve parçacık tabancası makroları.
2. `02_electromagnetic_showcase`: Fizik listelerini özelleştirme, GPS tabanlı ışın tanımlama, doz profilleri.
3. `03_multithread_run`: Çok çekirdekli (MT) çalıştırma, komut makroları ve `G4AnalysisManager` ile analiz.

## Derleme Şablonu

```sh
cmake -S . -B build -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0
cmake --build build
```

Çalıştırma adımında ilgili dizine giderek `./build/minimalDetector macros/run.mac` tarzında makroları parametre olarak ver. Makro dosyaları, deney parametrelerini kodu değiştirmeden yönetmeni sağlar.

## Neden Bu Sıra?

- **Bilimsel ilerleme:** Önce geometriyi tanıyorsun, ardından süreçleri (physics list), son olarak da performans ve veri toplama konularını pekiştiriyorsun.
- **İş değeri:** Simülasyon çıktılarının kurumsal raporlara veya ürün doğrulama süreçlerine entegrasyonu kademeli olarak mümkün hale geliyor.
- **Teknik kazanım:** CMake, makro komut dosyaları ve analiz araçlarını birlikte kullanma pratiği edinmiş oluyorsun.

## Önerilen Kaynaklar

- Geant4 Application Developers Guide: Dedektör inşası, birincil üreticiler (primary generators) ve aksiyon sınıfları bölümleri.
- Geant4’ün resmi örnekleri: `examples/basic/B1`, `B3` ve `extended/analysis` klasörleri bu modüllerle paralel konular içeriyor.

Her alt klasörde Türkçe rehberler seni adım adım yönlendirir. Hazırlık olarak `geant4.sh` betiğini çalıştırmayı unutma; aksi halde veri setleri bulunamadığında hata alırsın.
