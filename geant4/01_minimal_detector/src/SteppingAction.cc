#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include <G4LogicalVolume.hh>
#include <G4Step.hh>

SteppingAction::SteppingAction(const DetectorConstruction *detector, EventAction *eventAction)
    : G4UserSteppingAction(), fDetector(detector), fEventAction(eventAction) {
    if (fDetector) {
        fScoringVolume = fDetector->GetScoringVolume();
    }
}

void SteppingAction::UserSteppingAction(const G4Step *step) {
    if (!fScoringVolume) {
        return;
    }

    auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if (volume != fScoringVolume) {
        return;
    }

    auto edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.) {
        return;
    }

    if (fEventAction) {
        fEventAction->AddEdep(edep);
    }
}
