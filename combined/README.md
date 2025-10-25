# ROOT + Geant4 Entegrasyon Rotası

Bu bölüm, Geant4 simülasyonlarından çıkan verileri ROOT analiz hattına nasıl bağlayacağını anlatır. Genel akış şu şekilde işler:

1. Geant4 uygulaması `G4AnalysisManager` (veya özel sınıflar) aracılığıyla vuruşları ve ntuple verilerini `.root` dosyalarına yazar.
2. ROOT / PyROOT betikleri bu dosyaları okuyarak hızlı görselleştirme, eşik uygulama ve uydurma (fitting) yapar.

## Proje

1. `01_g4_to_root`: Geant4 tarafında silisyum teleskop simülasyonu, ROOT tarafında ise hem C++ hem PyROOT ile analiz.

## Önerilen Çalışma Şekli

- Önce Geant4 uygulamasını derleyip çalıştırarak örnek `.root` dosyasını üret.
- Ardından ROOT makrosu ve PyROOT betiğiyle dağılımları çiz, fiziksel yorumunu yap ve daha fazla türetilmiş büyüklük hesapla.
- Kendi dedektör geometri şemanı işlemek istersen, dallara yeni alanlar ekleyerek şemayı genişlet.
- İş değeri: Simülasyon çıktısı ile analizi tek döngüde birleştirerek Ar-Ge ekibine hız kazandır, deneysel doğrulamaya gitmeden önce sonuçları filtrele.

Tüm açıklamalar Türkçe olduğundan gerçek bir proje hazırlığına başlamadan önce burada ellerini ısıtabilirsin.
