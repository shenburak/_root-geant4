#pragma once

#include <G4VUserActionInitialization.hh>

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization {
  public:
    explicit ActionInitialization(const DetectorConstruction *detector);
    ~ActionInitialization() override = default;

    void Build() const override;

  private:
    const DetectorConstruction *fDetector{nullptr};
};
