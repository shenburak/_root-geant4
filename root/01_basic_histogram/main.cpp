#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStyle.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>

namespace {
// Çekirdek üreticiyi sistem zamanına göre kurarak her çalıştırmada farklı dağılım elde ediyoruz.
std::mt19937 MakeRng() {
    auto seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::mt19937{seed};
}

// Histogramı doldurmak için iki farklı rastgele dağılımı harmanlıyoruz: düz spektrum ve üstel gürültü.
void FillHistogram(TH1F &hist, std::size_t nEvents) {
    auto rng = MakeRng();
    std::uniform_real_distribution<float> spectrum(0.F, 10.F);
    std::exponential_distribution<float> noise(1.5F);

    for (std::size_t i = 0; i < nEvents; ++i) {
        float value = spectrum(rng) + 0.4F * noise(rng);
        hist.Fill(value);
    }
}
}

int main(int argc, char **argv) {
    bool batchMode = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg{argv[i]};
        if (arg == "--batch") {
            batchMode = true;
        }
    }

    // TApplication grafik arayüzünü başlatır; batch moddaysak kullanıcı etkileşimi olmadan devam edeceğiz.
    auto app = std::make_unique<TApplication>("histogram", &argc, argv);

    // Enerji spektrumunu temsil eden histogramı oluşturuyoruz.
    TH1F hist{"energy", "Toy Energy Spectrum;E [MeV];Counts", 100, 0., 12.};
    FillHistogram(hist, 25'000);

    TCanvas canvas{"c1", "Energy Canvas", 800, 600};
    gStyle->SetOptStat(1110);
    hist.SetLineColor(kAzure + 1);
    hist.SetFillColorAlpha(kAzure - 9, 0.35);
    hist.Draw();

    // TFile aracılığıyla ROOT dosyasına hem histogram hem kanvası kaydediyoruz.
    TFile output{"output.root", "RECREATE"};
    hist.Write();
    canvas.Write();
    canvas.SaveAs("energy_canvas.png");

    // Batch mod açık değilse interaktif olarak kanvası göster ve kullanıcıdan çıkış bekle.
    if (!batchMode) {
        canvas.Update();
        app->Run();
    }

    std::cout << "Histogram stored in output.root and energy_canvas.png\n";
    return 0;
}
