#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
   RegisterPhysics (new G4EmStandardPhysics());
   RegisterPhysics (new G4EmStandardPhysics_option4());

   // for gamma particles
   //RegisterPhysics(new G4EmLivermorePhysics());
   //RegisterPhysics(new G4DecayPhysics());
   //RegisterPhysics(new G4RadioactiveDecayPhysics());

   // for optical photons
   // RegisterPhysics (new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
