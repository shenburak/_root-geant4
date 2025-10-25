#pragma once

#include <G4UserSteppingAction.hh>

#include <unordered_map>

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
    std::unordered_map<const G4LogicalVolume *, std::size_t> fLayerIndex;
};
