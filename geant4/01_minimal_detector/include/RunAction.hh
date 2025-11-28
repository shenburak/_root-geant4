#pragma once

#include <G4Accumulable.hh>
#include <G4AccumulableManager.hh>
#include <G4UserRunAction.hh>

class RunAction : public G4UserRunAction {
  public:
    RunAction();
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run *) override;
    void EndOfRunAction(const G4Run *) override;

    void AddEdep(G4double edep);

  private:
    G4Accumulable<G4double> fTotalEdep;
};
