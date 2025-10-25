void viewHits(const char *filePath = "output/telescope_hits.root") {
    auto file = TFile::Open(filePath, "READ");
    if (!file || file->IsZombie()) {
        Error("viewHits", "Cannot open %s", filePath);
        return;
    }

    auto tree = dynamic_cast<TTree *>(file->Get("hits"));
    if (!tree) {
        Error("viewHits", "Tree 'hits' not found in %s", filePath);
        return;
    }

    auto canvas = std::make_unique<TCanvas>("c_hits", "Telescope hits", 1000, 500);
    canvas->Divide(2, 1);

    canvas->cd(1);
    // Enerji depozisyonunu hızlıca gözlemlemek için tek boyutlu histogram çiziyoruz.
    tree->Draw("energy_keV>>hE(100,0,400)");
    auto *hE = dynamic_cast<TH1 *>(gPad->FindObject("hE"));
    if (hE) {
        hE->SetLineColor(kAzure + 1);
        hE->SetTitle("Energy deposition;Energy [keV];Counts");
    }

    canvas->cd(2);
    // Katman-z dağılımı, teleskop dizilimindeki saçılma profilini okumayı kolaylaştırır.
    tree->Draw("z_mm:layer_id", "", "colz");
    gPad->SetRightMargin(0.15);

    canvas->SaveAs("telescope_hits_overview.png");
    file->Close();
}
