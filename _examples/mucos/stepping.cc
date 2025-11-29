#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction* ea){
   fEventAction = ea;
}

MySteppingAction::~MySteppingAction() { }

void MySteppingAction::UserSteppingAction(const G4Step* step){
   G4double energyDeposition = step->GetTotalEnergyDeposit();
   fEventAction->AddEdep(energyDeposition);
}
