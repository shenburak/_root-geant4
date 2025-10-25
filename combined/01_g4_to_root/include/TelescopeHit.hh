#pragma once

#include <G4ThreeVector.hh>
#include <G4VHit.hh>
#include <G4THitsCollection.hh>

class TelescopeHit : public G4VHit {
  public:
    TelescopeHit() = default;
    ~TelescopeHit() override = default;

    void SetEventId(G4int id) { fEventId = id; }
    void SetLayerId(G4int id) { fLayerId = id; }
    void SetEnergy(G4double energy) { fEnergy = energy; }
    void SetPosition(const G4ThreeVector &position) { fPosition = position; }
    void SetTime(G4double time) { fTime = time; }

    G4int GetEventId() const { return fEventId; }
    G4int GetLayerId() const { return fLayerId; }
    G4double GetEnergy() const { return fEnergy; }
    const G4ThreeVector &GetPosition() const { return fPosition; }
    G4double GetTime() const { return fTime; }

  private:
    G4int fEventId{0};
    G4int fLayerId{0};
    G4double fEnergy{0.0};
    G4ThreeVector fPosition{0., 0., 0.};
    G4double fTime{0.0};
};

using TelescopeHitsCollection = G4THitsCollection<TelescopeHit>;
