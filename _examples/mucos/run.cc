#include "run.hh"

MyRunAction::MyRunAction()  {
    // get anayisis pointer
    auto *man = G4AnalysisManager::Instance();

    // Determine the NTuple contents (I for integer, D for double)
    // Hit info on the sensitive detector
    man->CreateNtuple("Hits","Hits");
    man->CreateNtupleIColumn("Event");
    man->CreateNtupleIColumn("PDGcode");
    man->CreateNtupleDColumn("pmag");
    man->CreateNtupleDColumn("px");
    man->CreateNtupleDColumn("py");
    man->CreateNtupleDColumn("pz");
    man->CreateNtupleDColumn("x");
    man->CreateNtupleDColumn("y");
    man->CreateNtupleDColumn("z");
    man->FinishNtuple(0);

    // Energy deposition inside the material
    man->CreateNtuple("Scoring","Scoring");
    man->CreateNtupleDColumn("fEdep");
    man->FinishNtuple(1);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run){
    // get anayisis pointer
    auto *man = G4AnalysisManager::Instance();

    // open root files for each run
    G4int RunNum = run->GetRunID();
    std::stringstream strRunNum;
    strRunNum << RunNum;
    man->OpenFile("output" + strRunNum.str() + ".root");
}

void MyRunAction::EndOfRunAction(const G4Run*){
    // write the values to file and close at the end of run
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}
