#include "TelescopeSD.hh"

#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4ThreeVector.hh>

TelescopeSD::TelescopeSD(const G4String &name) : G4VSensitiveDetector(name) {
    collectionName.insert("TelescopeHits");
}

void TelescopeSD::Initialize(G4HCofThisEvent *hce) {
    fHitsCollection = new TelescopeHitsCollection(SensitiveDetectorName, collectionName[0]);

    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fHCID, fHitsCollection);
}

G4bool TelescopeSD::ProcessHits(G4Step *step, G4TouchableHistory *) {
    auto edep = step->GetTotalEnergyDeposit();
    if (edep <= 0.) {
        return false;
    }

    auto hit = new TelescopeHit();
    hit->SetEnergy(edep);
    hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());
    hit->SetPosition(step->GetPreStepPoint()->GetPosition());
    hit->SetLayerId(step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());

    fHitsCollection->insert(hit);
    return true;
}
