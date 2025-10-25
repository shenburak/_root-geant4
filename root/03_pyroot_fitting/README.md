# 03 – PyROOT ile Uydurma (Fitting) ve Görselleştirme

Bu modülde Python’un hızını ROOT’un güçlü uydurma altyapısıyla birleştiriyoruz. Sentetik bir enerji spektrumu üreterek Gauss + arka plan modeliyle fit yapacak, belirsizlikleri hesaplayacak ve yayın kalitesinde görseller oluşturacağız.

## Gereksinimler

- Python 3.9 veya üzeri.
- PyROOT ortamda erişilebilir olmalı (`python3 -c "import ROOT"`).
- İsteğe bağlı: Karşılaştırmalı grafikler için `matplotlib` (ikinci betik kullanıyor).

## Kullanım

```sh
python3 spectrum_fit.py --events 50000 --noise 0.4
python3 overlay_with_matplotlib.py --input spectrum.root
```

- İlk betik sentetik veriyi üretir, Gauss + üstel arka plan modelini uydurur ve sonuçları `spectrum.root` ile `spectrum_fit.png` dosyalarına kaydeder.
- İkinci betik ROOT histogramını matplotlib çizimiyle üst üste getirir; böylece bilimsel makale veya sunum için hazır bir görsel elde edersin.

## Öne Çıkan Noktalar

- `TF1` ile parametrik uydurma, parametre sınırları ve başlangıç değerleri.
- Kovaryans matrisi üzerinden hata (belirsizlik) hesaplama ve raporlama.
- Kanvas stilizasyonu, lejant yönetimi ve çıktıyı `.png` olarak verme.
- numpy/matplotlib ile entegrasyon; kurum içi veri bilim ekipleriyle aynı dili konuşmanı sağlar.

## Adım Adım Rehber

1. `python3 spectrum_fit.py --batch` komutu ile arayüz göstermeden çalıştır; rapor için `fit_report.txt` dosyasını incele.
2. `spectrum.root` dosyasını `root -l spectrum.root` ile açıp `fit_model->Print()` komutu ile parametreleri kontrol et.
3. `overlay_with_matplotlib.py` çıktısı olan `spectrum_matplotlib.png` dosyasını aç; ROOT ve matplotlib çizimlerinin uyumunu değerlendir.
4. İş değeri: Fit sonucu parametreleri bir kalite metriği olarak düşün; tolerans dışına çıktığında alarm üretilebilir.

## Kendini Geliştir

- Dedektör çözünürlüğünü simüle etmek için iki Gauss’un toplamını dene ve sonuçların fiziksel yorumunu yaz.
- Fit parametrelerini `json` modülüyle `.json` dosyasına kaydederek veri hattına kolay entegrasyon sağla.
- `RooFit` dünyasına adım atmak için histogramı `RooDataHist` içine sar; betik içindeki yorum seni yönlendirecek.

Betikler içinde yer alan Türkçe yorumlar ne yaptığımızı ayrıntılı biçimde açıklar; adımları takip ederek PyROOT ile rahatça deney yapabilirsin.
