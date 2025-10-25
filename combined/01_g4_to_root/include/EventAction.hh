#pragma once

#include <G4UserEventAction.hh>

#include <string>
#include <vector>

class G4Event;
class RunAction;

class EventAction : public G4UserEventAction {
  public:
    EventAction(RunAction *runAction, std::size_t nLayers);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event *) override;
    void EndOfEventAction(const G4Event *event) override;

  private:
    RunAction *fRunAction{nullptr};
    std::size_t fNLayers{0};

    int fEventId{0};
};
