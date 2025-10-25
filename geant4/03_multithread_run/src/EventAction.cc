#include "EventAction.hh"
#include "RunAction.hh"

#include <G4Event.hh>

#include <algorithm>

EventAction::EventAction(RunAction *runAction, std::size_t nLayers)
    : G4UserEventAction(), fRunAction(runAction), fDeposits(nLayers, 0.0) {}

void EventAction::BeginOfEventAction(const G4Event *) {
    std::fill(fDeposits.begin(), fDeposits.end(), 0.0);
}

void EventAction::EndOfEventAction(const G4Event *) {
    if (!fRunAction) {
        return;
    }
    for (std::size_t i = 0; i < fDeposits.size(); ++i) {
        if (fDeposits[i] > 0.) {
            fRunAction->FillLayer(i, fDeposits[i]);
        }
    }
}

void EventAction::AddDeposit(std::size_t layer, G4double edep) {
    if (layer >= fDeposits.size()) {
        return;
    }
    fDeposits[layer] += edep;
}
