#pragma once

#include <G4VUserPrimaryGeneratorAction.hh>

#include <memory>

class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event *event) override;

    G4GeneralParticleSource *GetParticleSource() const { return fSource.get(); }

  private:
    std::unique_ptr<G4GeneralParticleSource> fSource;
};
