#include "PrimaryGeneratorAction.hh"

#include <G4Event.hh>
#include <G4GeneralParticleSource.hh>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    // GPS kullanarak makro tabanlı, çoklu enerji tanımlı ışın senaryolarını kolayca test edebiliyoruz.
    fSource = std::make_unique<G4GeneralParticleSource>();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() = default;

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {
    // Hit tabanlı analiz için her olayda GPS'in oluşturduğu parçacık verisini kaydediyoruz.
    fSource->GeneratePrimaryVertex(event);
}
