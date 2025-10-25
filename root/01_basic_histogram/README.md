# 01 – Histogram ve Kanvas ile Tanışma

Bu ilk örnek, ROOT kurulumunun eksiksiz çalıştığını doğrulaman için tasarlandı. Histogram üretmeyi, kanvası yönetmeyi ve sonuçları `.root` ile `.png` dosyalarına kaydetmeyi öğreneceksin. Kod içindeki Türkçe yorumlar seni yönlendiriyor, ayrıca aşağıdaki adımları takip etmen yeterli.

## Neden Önemli?

- **Bilimsel bakış:** Enerji spektrumları gibi dağılımları incelemek deney fiziğinin temelidir.
- **İş/tasarım bakışı:** Üretim süreçlerinde (ör. kalite kontrol) hızlı histogramlar üretmek karar vermeyi hızlandırır.
- **Teknik hedef:** ROOT uygulamasının baştan sona (derleme → çalışma → çıktı) sorunsuz olduğunu test etmek.

## Derleme

```sh
make
```

Bu komut `root-config` bayraklarını kullanarak `basic_histogram` ikilisini üretir.

## Çalıştırma

```sh
./basic_histogram
root -l output.root
```

ROOT kabuğuna girince `.ls` yazarak dosyaya kaydedilen nesneleri listele, `energy->Draw()` ya da `hist->Draw()` ile görüntüle. `energy_canvas.png` dosyası görsel olarak çıktı verir.

## Öğrenilecek Temel Kavramlar

- `TApplication` nesnesi ile uygulamayı grafikli veya batch modda başlatma.
- `TH1F` sınıfı ile histogram oluşturup doldurma.
- `TFile` üzerinden kalıcı `.root` kaydı alma.
- Kanvası `.png` olarak dışa aktarma ve raporlamada kullanma.

## Adım Adım Rehber

1. `make` çalıştır, hata varsa `root-config` yollarını kontrol et.
2. `./basic_histogram` komutu ile örneği başlat; konsolda yazan bilgilere dikkat et.
3. `root -l output.root` ile çıktı dosyasını aç, `hist->Print()` diyerek histogram özelliklerini incele.
4. Grafiği sunum veya rapor için `energy_canvas.png` dosyasından al.

## Kendini Test Et

- Dağılımı Gauss gürültüsü ile değiştirip şekillerin nasıl farklılaştığını gözlemle.
- İkinci bir histogram ekleyip `SetLineColor` ile üst üste çiz; çoklu dedektör kanalını simüle etmiş olursun.
- `./basic_histogram --batch` parametresiyle GUI’yi kapat; yüksek hacimli üretimde batch modu tercih edilir.

Not: Kod içindeki açıklamalar Türkçe olduğundan neyin neden yapıldığını adım adım takip edebilirsin. Değişiklik yaptığında yeni histogramı tekrar incelemeyi unutma.
