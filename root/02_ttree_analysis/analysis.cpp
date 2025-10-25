#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TFile.h>

#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::string inputPath = "events.root";
    if (argc > 1) {
        inputPath = argv[1];
    }

    ROOT::EnableImplicitMT();
    ROOT::RDataFrame df{"events", inputPath};

    auto energyHist = df.Histo1D({"h_energy_zoom", "Energy Zoom;E [MeV];Counts", 20, 2., 7.}, "energy");
    auto timeHist = df.Histo1D({"h_time", "Arrival Time;time [ns];Counts", 20, 8., 28.}, "time_ns");

    auto canvas = std::make_unique<TCanvas>("c_combo", "Energy & Time", 900, 400);
    canvas->Divide(2, 1);
    canvas->cd(1);
    energyHist->SetLineColor(kAzure + 1);
    energyHist->Draw();
    canvas->cd(2);
    timeHist->SetLineColor(kOrange + 7);
    timeHist->Draw();
    canvas->SaveAs("rdf_combo.png");

    auto outfile = std::unique_ptr<TFile>{TFile::Open("rdf_outputs.root", "RECREATE")};
    if (outfile && !outfile->IsZombie()) {
        energyHist->Write();
        timeHist->Write();
        outfile->Write();
    }

    std::cout << "Wrote histograms to rdf_outputs.root and rdf_combo.png\n";
    return 0;
}
