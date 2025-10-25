#include "PrimaryGeneratorAction.hh"

#include <G4Event.hh>
#include <G4GeneralParticleSource.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    // G4GeneralParticleSource makrolarla kolayca yapılandırılabildiği için daha gelişmiş çalışmalar için uygun.
    fParticleSource = std::make_unique<G4GeneralParticleSource>();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() = default;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
    // Her olay için GPS, makro dosyasında tanımlanan parçacığı üretir.
    fParticleSource->GeneratePrimaryVertex(event);
}
