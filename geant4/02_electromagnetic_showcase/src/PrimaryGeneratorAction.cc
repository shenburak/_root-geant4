#include "PrimaryGeneratorAction.hh"

#include <G4Event.hh>
#include <G4GeneralParticleSource.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleSource = std::make_unique<G4GeneralParticleSource>();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() = default;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
    fParticleSource->GeneratePrimaryVertex(event);
}
