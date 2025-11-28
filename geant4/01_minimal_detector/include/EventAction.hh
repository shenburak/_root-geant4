#pragma once

#include <G4Types.hh>
#include <G4UserEventAction.hh>

class RunAction;

class EventAction : public G4UserEventAction {
  public:
    explicit EventAction(RunAction *runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *) override;
    void EndOfEventAction(const G4Event *) override;

    void AddEdep(G4double edep) { fEventEdep += edep; }

  private:
    RunAction *fRunAction{nullptr};
    G4double fEventEdep{0.0};
};
