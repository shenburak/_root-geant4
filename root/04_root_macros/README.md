# 04 – ROOT Makroları ve Toplu (Batch) Otomasyon

Bu modülde ROOT makrolarını nasıl yapılandıracağını, parametreleri JSON ile nasıl yöneteceğini ve betikleri batch modda çalıştırarak tekrar eden işleri nasıl otomatikleştireceğini öğrenirsin. Gerçek hayatta sıkça karşılaşılan “aynı grafiği farklı parametrelerle defalarca üret” senaryosunu kolaylaştırıyoruz.

## Dosya Tanımları

- `spectrumMacro.C`: Parametre alarak histogram oluşturan ve bir `TCanvas*` döndüren makro. Türkçe yorumlar hangi adımda ne olduğunu anlatır.
- `config.json`: Farklı senaryoların parametre listesi. İster fizik çalışması ister ürün raporu olsun, tek dosyada senaryolarını sakla.
- `run_all.C`: Cling uyumlu sürücü makro. JSON’u okur, her senaryoyu çalıştırır ve çıktıları kaydeder.
- `batch.sh`: ROOT’u arayüz açmadan çalıştıran örnek kabuk betiği. CI/CD veya sunucuda iş planlamak için ideal.

## Kullanım

```sh
root -l -q 'run_all.C("config.json")'
./batch.sh
```

Her çalışma sonunda `output/` klasöründe isimlendirilmiş kanvaslar, `.root` dosyaları ve rapor niteliğinde görseller oluşturulur. Parametre seti arttıkça otomasyonun değeri katlanır.

## Rehberlik Notları

- Konfigürasyon JSON’u ROOT’un `TJSON` araçlarıyla okunuyor. Alan adlarını değiştirirken makrodaki karşılıklarını güncelle.
- `spectrumMacro.C` hem yorumlanabilir (`.x spectrumMacro.C`) hem derlenebilir (`.x spectrumMacro.C++`) yazıldı; performans ihtiyacına göre seç.
- `config.json` dosyasına kendi senaryolarını ekleyip çıktıları karşılaştır; örneğin iş tarafında farklı müşteri kullanım profilleri raporlanabilir.
- Batch modda çalışırken `--enable-implicitMT` gibi ek parametreler vererek çok çekirdekli çalışmayı test edebilirsin.

Bu modülü tamamladıktan sonra, ROOT tabanlı otomasyon hattı kurmaya hazır olacaksın. Düzenli rapor üretimi, veri kalibrasyonu ve simülasyon taramalarında bu yaklaşım sana zaman kazandırır.
