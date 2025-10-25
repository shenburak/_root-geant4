#pragma once

#include <G4VUserPrimaryGeneratorAction.hh>

#include <memory>

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event *event) override;

  private:
    std::unique_ptr<G4ParticleGun> fParticleGun;
};
