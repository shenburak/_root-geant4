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
#include <string>

int main(int argc, char **argv) {
    auto runManager = G4RunManagerFactory::CreateRunManager();
    // Geometri, fizik ve kullanıcı action sınıfları run manager'a inject ediliyor.
    runManager->SetUserInitialization(new DetectorConstruction());

    auto physicsList = new FTFP_BERT;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new ActionInitialization());

    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    const std::string macroArg = argc > 1 ? argv[1] : "";
    const bool wantsVisSession = (argc == 1) || (macroArg.find("init_vis") != std::string::npos);
    std::unique_ptr<G4UIExecutive> uiExec;
    if (wantsVisSession) {
        uiExec = std::make_unique<G4UIExecutive>(argc, argv);
    }

    if (argc == 1) {
        // Etkileşimli çalıştırmada görselleştirme betiğini çağırıp kullanıcıya terminal oturumu açıyoruz.
        uiManager->ApplyCommand("/control/execute macros/init_vis.mac");
        uiExec->SessionStart();
    } else {
        // Komut satırında makro dosyası verilmişse doğrudan yorumluyoruz.
        auto command = std::string("/control/execute ") + macroArg;
        uiManager->ApplyCommand(command);
        if (uiExec) {
            uiExec->SessionStart();
        }
    }

    return 0;
}
