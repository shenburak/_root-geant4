#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
   fParticleGun = new G4ParticleGun(1); // 1 partice = 1 primary vertex per event

   G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

   G4ParticleDefinition *particle = particleTable->FindParticle("proton");

   G4ThreeVector pos(0., 0., 0.); // initial position of particle
   G4ThreeVector mom(0., 0., 1.); // direction of particle

   fParticleGun->SetParticlePosition(pos);
   fParticleGun->SetParticleMomentumDirection(mom);
   fParticleGun->SetParticleMomentum(0.5*GeV);
   fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
   delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
   fParticleGun->GeneratePrimaryVertex(anEvent);
}
