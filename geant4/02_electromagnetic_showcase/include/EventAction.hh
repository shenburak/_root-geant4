#pragma once

#include <G4UserEventAction.hh>

#include <vector>

class RunAction;

class EventAction : public G4UserEventAction {
  public:
    EventAction(RunAction *runAction, std::size_t nLayers);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *) override;
    void EndOfEventAction(const G4Event *) override;

    void AddEdep(std::size_t layer, G4double edep);

  private:
    RunAction *fRunAction{nullptr};
    std::vector<G4double> fEventDeposits;
};
