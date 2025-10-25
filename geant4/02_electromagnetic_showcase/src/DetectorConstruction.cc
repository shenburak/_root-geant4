#include "DetectorConstruction.hh"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>

#include <G4MultiFunctionalDetector.hh>
#include <G4PSEnergyDeposit.hh>
#include <G4PSDoseDeposit.hh>

DetectorConstruction::DetectorConstruction() = default;

G4VPhysicalVolume *DetectorConstruction::Construct() {
    fLayerVolumes.clear();

    auto *nist = G4NistManager::Instance();

    auto *air = nist->FindOrBuildMaterial("G4_AIR");
    auto *silicon = nist->FindOrBuildMaterial("G4_Si");
    auto *lead = nist->FindOrBuildMaterial("G4_Pb");

    // Dünya hacmi geniş tutuldu; elektromanyetik duşlar sığacak şekilde beden ayarlandı.
    auto *worldSolid = new G4Box("WorldSolid", 2. * m, 2. * m, 2. * m);
    auto *worldLogical = new G4LogicalVolume(worldSolid, air, "WorldLogical");
    auto *worldPhysical = new G4PVPlacement(nullptr, {}, worldLogical, "WorldPhysical", nullptr, false, 0, true);

    const G4double layerThickness = 2.0 * cm;
    auto *stackSolid = new G4Box("StackSolid", 15. * cm, 15. * cm, 3.0 * layerThickness);
    auto *stackLogical = new G4LogicalVolume(stackSolid, air, "StackLogical");
    new G4PVPlacement(nullptr, {}, stackLogical, "StackPhysical", worldLogical, false, 0, true);

    // Lambda, izleme hacimlerindeki geometriyi tek noktadan define etmek için kullandığımız yardımcı fonksiyon.
    auto placeLayer = [&](const G4String &name, G4Material *material, G4double zOffset, const G4Colour &colour) {
        auto *solid = new G4Box(name + "Solid", 15. * cm, 15. * cm, 0.5 * layerThickness);
        auto *logical = new G4LogicalVolume(solid, material, name + "Logical");
        new G4PVPlacement(nullptr, G4ThreeVector(0., 0., zOffset), logical, name + "Physical", stackLogical, false, 0,
                          true);
        logical->SetVisAttributes(G4VisAttributes(colour));
        fLayerVolumes.push_back(logical);
    };

    placeLayer("Layer0", lead, -layerThickness, {0.3, 0.3, 0.3});
    placeLayer("Layer1", silicon, 0.0, {0.0, 0.5, 0.8});
    placeLayer("Layer2", silicon, layerThickness, {0.0, 0.7, 0.2});

    worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    stackLogical->SetVisAttributes(G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.1)));

    return worldPhysical;
}

void DetectorConstruction::ConstructSDandField() {
    auto *sdManager = G4SDManager::GetSDMpointer();

    for (std::size_t i = 0; i < fLayerVolumes.size(); ++i) {
        auto detectorName = "DoseLayer" + std::to_string(i);
        auto *mfd = new G4MultiFunctionalDetector(detectorName);
        sdManager->AddNewDetector(mfd);

        auto *edep = new G4PSEnergyDeposit("Edep");
        auto *dose = new G4PSDoseDeposit("Dose");
        // Aynı hacimde hem toplam enerji depozisyonunu hem de doz büyüklüğünü kaydediyoruz.
        mfd->RegisterPrimitive(edep);
        mfd->RegisterPrimitive(dose);

        SetSensitiveDetector(fLayerVolumes[i], mfd);
    }
}
