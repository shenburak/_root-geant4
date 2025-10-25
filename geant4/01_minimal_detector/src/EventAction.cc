#include "EventAction.hh"
#include "RunAction.hh"

#include <G4Event.hh>

EventAction::EventAction(RunAction *runAction) : G4UserEventAction(), fRunAction(runAction) {}

void EventAction::BeginOfEventAction(const G4Event *) {
    fEventEdep = 0.0;
}

void EventAction::EndOfEventAction(const G4Event *) {
    if (fRunAction) {
        fRunAction->AddEdep(fEventEdep);
    }
}
