#pragma once

#include <G4UserRunAction.hh>

#include <cstddef>

class RunAction : public G4UserRunAction {
  public:
    explicit RunAction(std::size_t nLayers);
    ~RunAction() override;

    void BeginOfRunAction(const G4Run *) override;
    void EndOfRunAction(const G4Run *) override;

  private:
    std::size_t fNLayers{0};
};
