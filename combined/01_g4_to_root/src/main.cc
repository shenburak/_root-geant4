#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

#include <FTFP_BERT.hh>

#include <G4RunManagerFactory.hh>
#include <G4UImanager.hh>

#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include <memory>
#include <string>

int main(int argc, char **argv) {
    auto runManager = G4RunManagerFactory::CreateRunManager();

    auto detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    auto physicsList = new FTFP_BERT;
    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new ActionInitialization(detector));

    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        auto uiExec = std::make_unique<G4UIExecutive>(argc, argv);
        uiManager->ApplyCommand("/control/execute macros/visual.mac");
        uiExec->SessionStart();
    } else {
        auto macro = std::string("/control/execute ") + argv[1];
        uiManager->ApplyCommand(macro.c_str());
    }

    return 0;
}
