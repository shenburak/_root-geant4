#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include <G4LogicalVolume.hh>
#include <G4Step.hh>

SteppingAction::SteppingAction(const DetectorConstruction *detector, EventAction *eventAction)
    : G4UserSteppingAction(), fDetector(detector), fEventAction(eventAction) {
    if (fDetector) {
        const auto &layers = fDetector->GetLayerVolumes();
        for (std::size_t i = 0; i < layers.size(); ++i) {
            // Katman hacimlerini indeksleyen bir tablo hazırlıyoruz ki adım sırasında hızlıca ulaşabilelim.
            fLayerIndex[layers[i]] = i;
        }
    }
}

void SteppingAction::UserSteppingAction(const G4Step *step) {
    if (!fEventAction) {
        return;
    }

    auto *logical = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    auto iter = fLayerIndex.find(logical);
    if (iter == fLayerIndex.end()) {
        return;
    }

    auto edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.) {
        return;
    }

    // Hangi katmanda enerji bırakıldıysa onu olay tamponuna ekliyoruz.
    fEventAction->AddEdep(iter->second, edep);
}
