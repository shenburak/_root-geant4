#pragma once

#include <G4VUserDetectorConstruction.hh>

#include <vector>

class G4LogicalVolume;
class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
  public:
    DetectorConstruction();
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume *Construct() override;
    void ConstructSDandField() override;

    const std::vector<G4LogicalVolume *> &GetLayerVolumes() const { return fLayers; }

  private:
    std::vector<G4LogicalVolume *> fLayers;
};
