#include "PrimaryGeneratorAction.hh"

#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    auto *particleTable = G4ParticleTable::GetParticleTable();
    auto *proton = particleTable->FindParticle("proton");

    fGun = std::make_unique<G4ParticleGun>(1);
    fGun->SetParticleDefinition(proton);
    fGun->SetParticleEnergy(150. * MeV);
    fGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fGun->SetParticlePosition(G4ThreeVector(0., 0., -1.5 * m));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() = default;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
    fGun->GeneratePrimaryVertex(event);
}
