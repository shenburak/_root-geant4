#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

#include <G4PhysListFactory.hh>
#include <G4RunManagerFactory.hh>
#include <G4UImanager.hh>

#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

namespace {
G4String ResolvePhysicsList(int argc, char **argv) {
    if (argc > 2) {
        return argv[2];
    }
    if (auto env = std::getenv("G4_PHYSICS")) {
        return env;
    }
    // Varsayılan olarak yüksek hassasiyetli elektromanyetik genişletmesi olan FTFP_BERT_EMZ seçiyoruz.
    return "FTFP_BERT_EMZ";
}
}

int main(int argc, char **argv) {
    auto runManager = G4RunManagerFactory::CreateRunManager();

    auto detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    auto physicsListName = ResolvePhysicsList(argc, argv);
    G4PhysListFactory physicsFactory;
    auto physicsList = physicsFactory.GetReferencePhysList(physicsListName);
    if (!physicsList) {
        std::cerr << "Unknown physics list '" << physicsListName << "', falling back to FTFP_BERT" << std::endl;
        // Kullanıcı hatalı isim verirse daha genel bir listeye dönüyoruz ki simülasyon yine de çalışsın.
        physicsList = physicsFactory.GetReferencePhysList("FTFP_BERT");
    }
    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new ActionInitialization(detector));

    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        auto uiExec = std::make_unique<G4UIExecutive>(argc, argv);
        // Etkileşimli mod otomatik olarak görselleştirme ve örnek makroları yükler.
        uiManager->ApplyCommand("/control/execute macros/init_vis.mac");
        uiExec->SessionStart();
    } else {
        auto macro = std::string("/control/execute ") + argv[1];
        // Toplu modda kullanıcı tarafından verilen makro betiği doğrudan çağırılır.
        uiManager->ApplyCommand(macro.c_str());
    }

    return 0;
}
