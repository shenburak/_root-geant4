#pragma once

#include <G4AccumulableManager.hh>
#include <G4UserRunAction.hh>

#include <vector>

class RunAction : public G4UserRunAction {
  public:
    explicit RunAction(std::size_t nLayers);
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run *) override;
    void EndOfRunAction(const G4Run *) override;

    void AddEdep(std::size_t layerIndex, G4double edep);

  private:
    std::vector<G4Accumulable<G4double>> fLayerDeposits;
};
