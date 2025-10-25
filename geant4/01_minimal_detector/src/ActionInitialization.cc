#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

#include <G4RunManager.hh>

void ActionInitialization::Build() const {
    auto detector = static_cast<const DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    auto runAction = new RunAction();
    SetUserAction(runAction);

    SetUserAction(new PrimaryGeneratorAction());

    auto eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    SetUserAction(new SteppingAction(detector, eventAction));
}
