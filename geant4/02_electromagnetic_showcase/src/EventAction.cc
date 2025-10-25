#include "EventAction.hh"
#include "RunAction.hh"

#include <G4Event.hh>

EventAction::EventAction(RunAction *runAction, std::size_t nLayers)
    : G4UserEventAction(), fRunAction(runAction), fEventDeposits(nLayers, 0.0) {}

void EventAction::BeginOfEventAction(const G4Event *) {
    // Her olay için katman başına enerji kayıtlarını sıfırlıyoruz.
    std::fill(fEventDeposits.begin(), fEventDeposits.end(), 0.0);
}

void EventAction::EndOfEventAction(const G4Event *) {
    if (!fRunAction) {
        return;
    }
    for (std::size_t i = 0; i < fEventDeposits.size(); ++i) {
        if (fEventDeposits[i] > 0.) {
            // RunAction katman bazlı toplamları Accumulable üzerinden tutuyor.
            fRunAction->AddEdep(i, fEventDeposits[i]);
        }
    }
}

void EventAction::AddEdep(std::size_t layer, G4double edep) {
    if (layer >= fEventDeposits.size()) {
        return;
    }
    // Her adımda gelen depozisyonları olay tamponuna ekliyoruz.
    fEventDeposits[layer] += edep;
}
