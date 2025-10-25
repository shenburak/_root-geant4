#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(const DetectorConstruction *detector)
    : G4VUserActionInitialization(), fDetector(detector) {}

void ActionInitialization::BuildForMaster() const {
    std::size_t nLayers = 0;
    if (fDetector) {
        // Master iş parçacığı analiz sonuçlarını toplamaktan sorumlu; katman sayısını önceden bilmesi gerek.
        nLayers = fDetector->GetLayerVolumes().size();
    }
    SetUserAction(new RunAction(nLayers, true));
}

void ActionInitialization::Build() const {
    std::size_t nLayers = 0;
    if (fDetector) {
        nLayers = fDetector->GetLayerVolumes().size();
    }

    auto runAction = new RunAction(nLayers, false);
    SetUserAction(runAction);

    SetUserAction(new PrimaryGeneratorAction());

    auto eventAction = new EventAction(runAction, nLayers);
    SetUserAction(eventAction);

    // SteppingAction hem geometri hem de olay arayüzünü kullanarak enerji depozisyonlarını paylaştırır.
    SetUserAction(new SteppingAction(fDetector, eventAction));
}
