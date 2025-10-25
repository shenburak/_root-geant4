#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

#include <FTFP_BERT.hh>

#include <G4RunManagerFactory.hh>
#include <G4Threading.hh>
#include <G4UImanager.hh>

#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

namespace {
G4int ResolveThreadCount() {
    if (auto env = std::getenv("G4THREADS")) {
        // Kullanıcı açıkça iş parçacığı sayısı sağladıysa onu min 1 olacak şekilde kullanıyoruz.
        return std::max<G4int>(1, std::atoi(env));
    }
    auto cores = G4Threading::G4GetNumberOfCores();
     // Sistem çekirdek sayısından bir eksik seçmek etkileşimli kullanımda sistemi kilitlemeyi önler.
    return std::max<G4int>(2, cores - 1);
}
}

int main(int argc, char **argv) {
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::MT);
    runManager->SetNumberOfThreads(ResolveThreadCount());

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
        // Etkileşimli modda çok iş parçacıklı makro özel çizim ve run parametrelerini ayarlar.
        uiManager->ApplyCommand("/control/execute macros/interactive.mac");
        uiExec->SessionStart();
    } else {
        auto macro = std::string("/control/execute ") + argv[1];
        // Toplu modda verilen makro çok iş parçacıklı olarak çalıştırılır.
        uiManager->ApplyCommand(macro.c_str());
    }

    return 0;
}
