# 01 – Geant4 Vuruşlarını ROOT’a Aktarma

Bu projede Geant4 ile silisyum teleskop simülasyonu yapıyor, oluşan vuruş (hit) bilgilerini bir ROOT ntuple’ına kaydediyor ve hem C++ hem PyROOT araçlarıyla analiz ediyoruz. Böylece tam bir simülasyon → analiz döngüsünü elinde tutmuş oluyorsun.

## Derleme

```sh
cmake -S . -B build \
  -DGeant4_DIR=$(geant4-config --prefix)/lib/Geant4-11.2.0 \
  -DROOT_DIR=$(root-config --prefix)
cmake --build build
```

## Simülasyonu Çalıştır

```sh
./build/telescope macros/proton.mac
```

Bu komut `output/telescope_hits.root` dosyasını üretir. Her vuruş için olay kimliği, katman, enerji kaybı, konum ve zaman bilgisi saklanır.

## ROOT ile Analiz Et

```sh
root -l -q 'analysis/viewHits.C("output/telescope_hits.root")'
python3 analysis/plot_hits.py --input output/telescope_hits.root
```

- `viewHits.C`: Hızlı enerji histogramı ve katman-z konum renk haritası oluşturur.
- `plot_hits.py`: PyROOT ile enerji dağılımı ve x-y etki haritasını çizer.

## Dosya Yapısı

- `src/`: Geant4 uygulaması, özel hit sınıfı (`TelescopeHit`) ve `G4AnalysisManager` entegrasyonu.
- `macros/`: Demet (beam) parametreleri ve görselleştirme makroları.
- `analysis/`: Üretilen veri setini inceleyen ROOT makrosu ve PyROOT betiği.

## Genişletme Fikirleri

- Teleskopa yeni katmanlar veya farklı malzemeler ekleyerek enerji kaybı profilini karşılaştır.
- `SteppingAction` tanımlayıp tüm parçacık izlerini ntuple’a yaz; radyasyon hasarı analizi yapabilirsin.
- PyROOT betiğine sinyal-gürültü oranı, verimlilik gibi metrikler ekleyip rapor hazırla.

Bu proje, Geant4 ve ROOT arasında veri alışverişinin temel mimarisini kavramanı sağlar. Kod içindeki Türkçe açıklamalar her sınıfın görevini adım adım açıklar.
