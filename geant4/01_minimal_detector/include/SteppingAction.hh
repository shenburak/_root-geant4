#pragma once

#include <G4UserSteppingAction.hh>

class DetectorConstruction;
class EventAction;
class G4LogicalVolume;
class G4Step;

class SteppingAction : public G4UserSteppingAction {
  public:
    SteppingAction(const DetectorConstruction *detector, EventAction *eventAction);
    ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step *step) override;

  private:
    const DetectorConstruction *fDetector{nullptr};
    EventAction *fEventAction{nullptr};
    G4LogicalVolume *fScoringVolume{nullptr};
};
