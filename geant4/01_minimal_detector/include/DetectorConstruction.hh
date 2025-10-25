#pragma once

#include <G4VUserDetectorConstruction.hh>

class G4LogicalVolume;
class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
  public:
    DetectorConstruction() = default;
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume *Construct() override;
    void ConstructSDandField() override;

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

  private:
    G4LogicalVolume *fScoringVolume{nullptr};
};
