#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(const DetectorConstruction *detector)
    : G4VUserActionInitialization(), fDetector(detector) {}

void ActionInitialization::Build() const {
    std::size_t nLayers = 0;
    if (fDetector) {
        // Dedektör katman sayısını action sınıflarına aktarabilmek için önceden okuyoruz.
        nLayers = fDetector->GetLayerVolumes().size();
    }

    auto runAction = new RunAction(nLayers);
    SetUserAction(runAction);

    SetUserAction(new PrimaryGeneratorAction());

    auto eventAction = new EventAction(runAction, nLayers);
    SetUserAction(eventAction);

    // SteppingAction enerji depozisyonlarını katman indeksine göre takip eder.
    SetUserAction(new SteppingAction(fDetector, eventAction));
}
