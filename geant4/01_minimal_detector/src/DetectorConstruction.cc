#include "DetectorConstruction.hh"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>

#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>

namespace {
G4LogicalVolume *FindLogicalVolume(const G4String &name) {
    auto store = G4LogicalVolumeStore::GetInstance();
    return store->GetVolume(name, false);
}
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    auto *nist = G4NistManager::Instance();

    auto *air = nist->FindOrBuildMaterial("G4_AIR");
    auto *silicon = nist->FindOrBuildMaterial("G4_Si");

    auto *worldSolid = new G4Box("WorldSolid", 1.0 * m, 1.0 * m, 1.0 * m);
    auto *worldLogical = new G4LogicalVolume(worldSolid, air, "WorldLogical");
    auto *worldPhysical = new G4PVPlacement(nullptr, {}, worldLogical, "WorldPhysical", nullptr, false, 0, true);

    auto *detectorSolid = new G4Box("DetectorSolid", 5.0 * cm, 5.0 * cm, 5.0 * cm);
    auto *detectorLogical = new G4LogicalVolume(detectorSolid, silicon, "DetectorLogical");
    new G4PVPlacement(nullptr, {}, detectorLogical, "DetectorPhysical", worldLogical, false, 0, true);

    worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    auto detectorColour = G4VisAttributes(G4Colour(0.0, 0.3, 0.9));
    detectorLogical->SetVisAttributes(detectorColour);

    fScoringVolume = detectorLogical;
    return worldPhysical;
}

void DetectorConstruction::ConstructSDandField() {
    if (!fScoringVolume) {
        fScoringVolume = FindLogicalVolume("DetectorLogical");
    }

    if (!fScoringVolume) {
        G4Exception("DetectorConstruction::ConstructSDandField", "NoScoringVolume", FatalException,
                    "Unable to locate scoring volume");
        return;
    }

    auto *sdManager = G4SDManager::GetSDMpointer();
    auto *mfd = new G4MultiFunctionalDetector("Calorimeter");
    sdManager->AddNewDetector(mfd);
    auto *edep = new G4PSEnergyDeposit("Edep");
    mfd->RegisterPrimitive(edep);
    SetSensitiveDetector(fScoringVolume, mfd);
}
