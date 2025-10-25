#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

#include <G4RunManagerFactory.hh>
#include <G4UImanager.hh>
#include <G4VModularPhysicsList.hh>

#include <FTFP_BERT.hh>

#ifdef G4MULTITHREADED
#include <G4MTRunManager.hh>
#endif

#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include <memory>

int main(int argc, char **argv) {
    auto runManager = G4RunManagerFactory::CreateRunManager();
    runManager->SetUserInitialization(new DetectorConstruction());

    auto physicsList = new FTFP_BERT;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new ActionInitialization());

    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        auto uiExec = std::make_unique<G4UIExecutive>(argc, argv);
        uiManager->ApplyCommand("/control/execute macros/init_vis.mac");
        uiExec->SessionStart();
    } else {
        auto command = std::string("/control/execute ") + argv[1];
        uiManager->ApplyCommand(command);
    }

    return 0;
}
