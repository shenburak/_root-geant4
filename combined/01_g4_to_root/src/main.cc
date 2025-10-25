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
    // Geometri ve hassas dedektörler run manager'a kaydediliyor.
    runManager->SetUserInitialization(detector);

    auto physicsList = new FTFP_BERT;
    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new ActionInitialization(detector));

    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        auto uiExec = std::make_unique<G4UIExecutive>(argc, argv);
        // Etkileşimli modda görselleştirme ve GPS ayarları visual.mac dosyasında toplanıyor.
        uiManager->ApplyCommand("/control/execute macros/visual.mac");
        uiExec->SessionStart();
    } else {
        auto macro = std::string("/control/execute ") + argv[1];
        // Toplu analizde parametre taramaları için farklı makrolar geçilebilir.
        uiManager->ApplyCommand(macro.c_str());
    }

    return 0;
}
