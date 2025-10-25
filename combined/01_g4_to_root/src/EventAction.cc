#include "EventAction.hh"
#include "RunAction.hh"
#include "TelescopeHit.hh"

#include <G4AnalysisManager.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>

namespace {
G4int FetchCollectionID() {
    static G4int id = -1;
    if (id < 0) {
        // Hit koleksiyonunu sadece ilk seferde SD yöneticisinden çekip kimliği önbelleğe alıyoruz.
        id = G4SDManager::GetSDMpointer()->GetCollectionID("TelescopeSD/TelescopeHits");
    }
    return id;
}
}

EventAction::EventAction(RunAction *runAction, std::size_t nLayers)
    : G4UserEventAction(), fRunAction(runAction), fNLayers(nLayers) {}

void EventAction::BeginOfEventAction(const G4Event *event) {
    // Olay kimliği ntuple'da anahtar olarak kullanılacak.
    fEventId = event->GetEventID();
}

void EventAction::EndOfEventAction(const G4Event *event) {
    auto *hce = event->GetHCofThisEvent();
    if (!hce) {
        return;
    }

    auto hcId = FetchCollectionID();
    auto *hits = static_cast<TelescopeHitsCollection *>(hce->GetHC(hcId));
    if (!hits) {
        return;
    }

    auto *analysis = G4AnalysisManager::Instance();
    for (const auto *hit : *hits) {
        // Her hit'i satır bazlı ntuple'lara yayarak PyROOT sonrası analizine hazır hale getiriyoruz.
        analysis->FillNtupleIColumn(0, fEventId);
        analysis->FillNtupleIColumn(1, hit->GetLayerId());
        analysis->FillNtupleDColumn(2, hit->GetEnergy() / keV);
        const auto &pos = hit->GetPosition();
        analysis->FillNtupleDColumn(3, pos.x() / mm);
        analysis->FillNtupleDColumn(4, pos.y() / mm);
        analysis->FillNtupleDColumn(5, pos.z() / mm);
        analysis->FillNtupleDColumn(6, hit->GetTime() / ns);
        analysis->AddNtupleRow();
    }
}
