#include "PrimaryGeneratorAction.hh"

#include <G4Electron.hh>
#include <G4GeneralParticleSource.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    auto particleTable = G4ParticleTable::GetParticleTable();
    auto particle = particleTable->FindParticle("e-");

    // Tek parçacıklı bir G4ParticleGun kuruyoruz; eğitim amaçlı olduğundan basit elektron demeti yeterli.
    fParticleGun = std::make_unique<G4ParticleGun>(1);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(5.0 * MeV);
    // Kaynağı detektör giriş yüzeyinden yeterince uzakta konumlayıp z ekseni boyunca ateşliyoruz.
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -30. * cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() = default;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
    // Her olayda tek bir tepe noktasını (primary vertex) taklit ediyoruz.
    fParticleGun->GeneratePrimaryVertex(event);
}
