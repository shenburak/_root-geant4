#include "RunAction.hh"

#include <G4AnalysisManager.hh>
#include <G4Run.hh>
#include <G4SystemOfUnits.hh>

#include <filesystem>
#include <string>

namespace {
void EnsureOutputDir() {
    std::filesystem::create_directories("output");
}
}

RunAction::RunAction(std::size_t nLayers, bool isMaster) : fNLayers(nLayers), fIsMaster(isMaster) {
    EnsureOutputDir();
    auto *analysis = G4AnalysisManager::Instance();
    analysis->SetFileName("output/mt_run");
    analysis->SetVerboseLevel(0);
    analysis->SetActivation(true);

    fHistogramIds.reserve(fNLayers);
    for (std::size_t i = 0; i < fNLayers; ++i) {
        auto name = "edep_layer" + std::to_string(i);
        auto title = "Energy deposit layer " + std::to_string(i) + ";Edep [MeV];Counts";
        auto id = analysis->CreateH1(name, title, 100, 0., 50.);
        fHistogramIds.push_back(id);
    }
}

RunAction::~RunAction() {
    if (fIsMaster) {
        delete G4AnalysisManager::Instance();
    }
}

void RunAction::BeginOfRunAction(const G4Run *) {
    auto *analysis = G4AnalysisManager::Instance();
    analysis->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run *) {
    auto *analysis = G4AnalysisManager::Instance();
    analysis->Write();
    analysis->CloseFile();
}

void RunAction::FillLayer(std::size_t layer, G4double edep) {
    if (layer >= fHistogramIds.size()) {
        return;
    }
    auto *analysis = G4AnalysisManager::Instance();
    analysis->FillH1(fHistogramIds[layer], edep / MeV);
}
