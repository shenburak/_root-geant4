# 02 – TTree Dönüşümü ve RDataFrame Analizi

Bu modülde CSV formatındaki yapılandırılmış veriyi `TTree`’ye dönüştürüp modern `RDataFrame` arayüzüyle analiz edeceğiz. Böylece gerçek deney verilerini analiz etmek için ihtiyaç duyacağın temel adımları görmüş olacaksın.

## Neden Önemli?

- **Bilimsel:** Olay (event) tabanlı veri depolamak yüksek enerjili fizik deneylerinin standart yaklaşımıdır.
- **İş:** Sensör ağlarından veya üretim hatlarından gelen log verilerini kolon bazlı tutup hızlı sorgulamak mümkündür.
- **Teknik:** C++ ve modern ROOT API’lerini birleştirerek performanslı veri hazırlığı yapmayı öğrenirsin.

## Çalışma Akışı

1. Yardımcı uygulamayı derleyip çalıştırarak `events.root` dosyasını oluştur.
2. ROOT kabuğunda ağacın (tree) yapısını inceleyip toplu kontroller yap.
3. Dahili RDataFrame analizini veya `analysis` uygulamasını çalıştırarak histogram ve özet tablolar üret.
4. Çıkan sonuçları iş ve bilimsel yorumlarla değerlendir.

## Derleme ve Çalıştırma

```sh
make
./ingest --csv data/events.csv --out events.root
root -l events.root
```

ROOT içinde:

```cpp
TTree *tree = nullptr;
file->GetObject("events", tree);
tree->Print();
tree->Draw("energy>>h(40,0,8)");
```

## Dosya Rehberi

- `main.cpp`: CSV dosyasını okuyup `TTree` oluşturur, ardından `RDataFrame` ile temel analizleri tetikler.
- `analysis.cpp`: Ek filtreler ve grafikler için bağımsız çalıştırabileceğin analiz aracı.
- `data/events.csv`: Küçük örnek veri seti. Kendi verini ekleyip süreci tekrar deneyebilirsin.

## Adım Adım Senaryo

1. `./ingest --csv data/events.csv --out events.root` komutunu çalıştır; kaç satır işlendiği konsolda görünür.
2. `root -l events.root` ile dosyayı aç, `tree->Scan("energy:time_ns")` komutu ile birkaç satırı incele.
3. `analysis` uygulamasını çalıştır (`./analysis events.root`) ve üretilen grafiklerin (`rdf_combo.png`) proje dizininde oluştuğunu doğrula.
4. İş senaryosu: Enerjisi 4.5 MeV üstü olayları `events_high.root` dosyasına `Snapshot` ile al. Böylece kalite kontrol için özel veri seti hazırlar gibi düşün.

## Deney ve Gelişim Fikirleri

- CSV’ye yeni bir sütun (örn. `temperature`) ekle, `main.cpp`’de ilgili dalı oluştur ve fiziksel yorumunu yap.
- CSV okuma kısmını `ROOT::RDF::MakeCsvDataFrame` ile değiştirerek kodu sadeleştir; performans farkını ölç.
- `RDataFrame::Snapshot` çıktısını farklı filtrelerle çoğalt, örneğin enerji aralıklarına göre ayrı dosyalar üret.

Her denemenin sonunda oluşan `.root` ve `.png` dosyalarını inceleyerek öğrendiklerini pekiştir. Kod içindeki Türkçe yorumlar seni yönlendirmek için güncellendi.
