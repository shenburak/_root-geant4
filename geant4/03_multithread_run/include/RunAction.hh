#pragma once

#include <G4Types.hh>
#include <G4UserRunAction.hh>

#include <vector>

class RunAction : public G4UserRunAction {
  public:
    RunAction(std::size_t nLayers, bool isMaster);
    ~RunAction() override;

    void BeginOfRunAction(const G4Run *) override;
    void EndOfRunAction(const G4Run *) override;

    void FillLayer(std::size_t layer, G4double edep);

  private:
    std::size_t fNLayers{0};
    bool fIsMaster{false};
    std::vector<G4int> fHistogramIds;
};
