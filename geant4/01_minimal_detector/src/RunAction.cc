#include "RunAction.hh"

#include <G4AccumulableManager.hh>
#include <G4Run.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

#include <iomanip>
#include <iostream>

RunAction::RunAction() : G4UserRunAction(), fTotalEdep(0.) {
    auto *accumulableManager = G4AccumulableManager::Instance();
    // Çok iş parçacıklı koşularda enerji toplamını güvenle toplayabilmek için Accumulable mekanizmasını kullanıyoruz.
    accumulableManager->Register(fTotalEdep);
}

void RunAction::BeginOfRunAction(const G4Run *) {
    auto *accumulableManager = G4AccumulableManager::Instance();
    // Her run başlangıcında önceki toplamlardan kurtulmak kritik.
    accumulableManager->Reset();
}

void RunAction::EndOfRunAction(const G4Run *run) {
    auto *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    auto nEvents = run->GetNumberOfEvent();
    if (nEvents == 0) {
        return;
    }

    auto totalEdep = fTotalEdep.GetValue();
    std::cout << "\nRun summary\n";
    std::cout << "Events: " << nEvents << '\n';
    std::cout << "Total energy deposit: " << G4BestUnit(totalEdep, "Energy") << '\n';
    std::cout << "Mean energy deposit per event: " << G4BestUnit(totalEdep / nEvents, "Energy") << '\n';
}

void RunAction::AddEdep(G4double edep) {
    // SteppingAction koşusu sırasında her adımda toplanan enerjiye ekleme yapıyoruz.
    fTotalEdep += edep;
}
