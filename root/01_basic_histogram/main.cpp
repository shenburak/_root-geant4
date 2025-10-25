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
std::mt19937 MakeRng() {
    auto seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::mt19937{seed};
}

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

    auto app = std::make_unique<TApplication>("histogram", &argc, argv);

    TH1F hist{"energy", "Toy Energy Spectrum;E [MeV];Counts", 100, 0., 12.};
    FillHistogram(hist, 25'000);

    TCanvas canvas{"c1", "Energy Canvas", 800, 600};
    gStyle->SetOptStat(1110);
    hist.SetLineColor(kAzure + 1);
    hist.SetFillColorAlpha(kAzure - 9, 0.35);
    hist.Draw();

    TFile output{"output.root", "RECREATE"};
    hist.Write();
    canvas.Write();
    canvas.SaveAs("energy_canvas.png");

    if (!batchMode) {
        canvas.Update();
        app->Run();
    }

    std::cout << "Histogram stored in output.root and energy_canvas.png\n";
    return 0;
}
