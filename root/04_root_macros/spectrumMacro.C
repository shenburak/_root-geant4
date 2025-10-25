#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TROOT.h>
#include <TSystem.h>

#include <cstdio>
#include <memory>
#include <sstream>
#include <string>

TCanvas *spectrumMacro(int entries = 20000,
                       double mean = 6.0,
                       double sigma = 1.0,
                       double background = 0.3,
                       const char *label = "default",
                       const char *outDir = "output") {
    // Çıktı dizini yoksa ROOT'un platform bağımsız mkdir fonksiyonuyla oluşturuyoruz.
    gSystem->mkdir(outDir, true);

    auto histName = Form("h_%s", label);
    auto histTitle = Form("Spectrum %s;Energy [MeV];Counts", label);
    // Histograma benzersiz isim verip akıllı işaretçiyle yönetiyoruz ki bellek sızıntısı olmasın.
    auto hist = std::make_unique<TH1F>(histName, histTitle, 120, 0.0, 12.0);

    TRandom3 rng(0);
    // Her olay için rastgele sinyal veya arka plan dağılımından numune çekiyoruz.
    for (int i = 0; i < entries; ++i) {
        double draw = rng.Uniform();
        double value = 0.0;
        if (draw < background) {
            value = rng.Exp(2.5) + 1.5;
        } else {
            value = rng.Gaus(mean, sigma);
        }
        hist->Fill(value);
    }

    auto canvasName = Form("c_%s", label);
    auto canvas = std::make_unique<TCanvas>(canvasName, canvasName, 800, 600);
    hist->SetLineColor(kAzure + 2);
    hist->SetFillColorAlpha(kAzure - 9, 0.35);
    hist->Draw();

    auto pngPath = Form("%s/%s.png", outDir, canvasName);
    // Her makro çağrısında görsel çıktıyı saklayarak hızlı kalite kontrol sağlıyoruz.
    // SaveAs aynı zamanda PDF gibi başka formatlara da kolayca uyarlanabilir.
    canvas->SaveAs(pngPath);

    auto rootPath = Form("%s/run_%s.root", outDir, label);
    auto file = std::unique_ptr<TFile>(TFile::Open(rootPath, "RECREATE"));
    if (file && !file->IsZombie()) {
        // Histogram ve tuvali ROOT dosyasına yazarak daha sonra PyROOT analizleriyle tekrar açabiliriz.
        hist->Write();
        canvas->Write();
        file->Write();
        file->Close();
    }

    return canvas.release();
}
