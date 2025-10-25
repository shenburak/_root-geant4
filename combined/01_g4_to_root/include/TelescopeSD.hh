#pragma once

#include "TelescopeHit.hh"

#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class TelescopeSD : public G4VSensitiveDetector {
  public:
    explicit TelescopeSD(const G4String &name);
    ~TelescopeSD() override = default;

    void Initialize(G4HCofThisEvent *hce) override;
    G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;

  private:
    TelescopeHitsCollection *fHitsCollection{nullptr};
    G4int fHCID{-1};
};
