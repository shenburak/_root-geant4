#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
  // get track (any particle)
  G4Track *track = aStep->GetTrack();
  track->SetTrackStatus(fStopAndKill);

  // event number and particle pdg code
  G4int pdgcode = track->GetParticleDefinition()->GetPDGEncoding();
  G4int event   = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // here we select proton and pi-
  if (pdgcode == 2212 || pdgcode == -211)
  {
        // momentum vector and magnitude
        G4ThreeVector pvec = track->GetMomentum();
        G4double      pmag = pvec.mag();
        G4ThreeVector posi = track->GetPosition(); // on detector

        // fill ntuple
        G4AnalysisManager *man = G4AnalysisManager::Instance();
        man->FillNtupleIColumn(0,event);
        man->FillNtupleIColumn(1,pdgcode);
        man->FillNtupleDColumn(2,pmag);
        man->FillNtupleDColumn(3,pvec[0]); // px
        man->FillNtupleDColumn(4,pvec[1]); // py
        man->FillNtupleDColumn(5,pvec[2]); // pz
        man->FillNtupleDColumn(6,posi[0]); // x
        man->FillNtupleDColumn(7,posi[1]); // y
        man->FillNtupleDColumn(8,posi[2]); // z
        man->AddNtupleRow(0);

        // print info to the screen
        //G4cout << event <<" " << pdgcode <<" " << pvec << " " << posi << G4endl;
  }

  return true;
}
