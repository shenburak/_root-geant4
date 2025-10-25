#include "EventAction.hh"
#include "RunAction.hh"

#include <G4Event.hh>

EventAction::EventAction(RunAction *runAction) : G4UserEventAction(), fRunAction(runAction) {}

void EventAction::BeginOfEventAction(const G4Event *) {
    // Her olay başında o olaya ait enerji toplamını sıfırlıyoruz.
    fEventEdep = 0.0;
}

void EventAction::EndOfEventAction(const G4Event *) {
    if (fRunAction) {
        // Olay sonunda toplanan enerji değeri RunAction üzerinden koşu toplamına ekleniyor.
        fRunAction->AddEdep(fEventEdep);
    }
}
