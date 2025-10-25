#include "RunAction.hh"

#include <G4AccumulableManager.hh>
#include <G4Run.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

#include <iostream>

RunAction::RunAction(std::size_t nLayers) {
    fLayerDeposits.reserve(nLayers);
    auto *accManager = G4AccumulableManager::Instance();
    for (std::size_t i = 0; i < nLayers; ++i) {
        fLayerDeposits.emplace_back(0.0);
        // Her katman için ayrı Accumulable nesnesi kaydediyoruz; MT koşularda eşzamanlı toplama sağlar.
        accManager->RegisterAccumulable(fLayerDeposits.back());
    }
}

void RunAction::BeginOfRunAction(const G4Run *) {
    auto *accManager = G4AccumulableManager::Instance();
    // Run başlarken bir önceki koşudan kalan değerler temizlenir.
    accManager->Reset();
}

void RunAction::EndOfRunAction(const G4Run *run) {
    auto *accManager = G4AccumulableManager::Instance();
    accManager->Merge();

    auto nEvents = run->GetNumberOfEvent();
    if (nEvents == 0) {
        return;
    }

    std::cout << "\nDose summary (" << nEvents << " events)\n";
    for (std::size_t i = 0; i < fLayerDeposits.size(); ++i) {
        auto value = fLayerDeposits[i].GetValue();
        // Doz çıktısını SI birim sistemindeki uygun büyüklükle raporluyoruz.
        std::cout << "Layer " << i << ": " << G4BestUnit(value, "Dose") << '\n';
    }
}

void RunAction::AddEdep(std::size_t layerIndex, G4double edep) {
    if (layerIndex >= fLayerDeposits.size()) {
        return;
    }
    // Olay bazlı katkı RunAction içinde katman indeksine göre toplanır.
    fLayerDeposits[layerIndex] += edep;
}
