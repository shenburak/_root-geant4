#include "RunAction.hh"

#include <G4AnalysisManager.hh>
#include <G4Run.hh>

#include <filesystem>

RunAction::RunAction(std::size_t nLayers) : fNLayers(nLayers) {
    std::filesystem::create_directories("output");

    auto *analysis = G4AnalysisManager::Instance();
    analysis->SetFileName("output/telescope_hits");
    analysis->SetVerboseLevel(0);

    analysis->CreateNtuple("hits", "Telescope hits");
    analysis->CreateNtupleIColumn("event_id");
    analysis->CreateNtupleIColumn("layer_id");
    analysis->CreateNtupleDColumn("energy_keV");
    analysis->CreateNtupleDColumn("x_mm");
    analysis->CreateNtupleDColumn("y_mm");
    analysis->CreateNtupleDColumn("z_mm");
    analysis->CreateNtupleDColumn("time_ns");
    analysis->FinishNtuple();
}

RunAction::~RunAction() {
    delete G4AnalysisManager::Instance();
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
