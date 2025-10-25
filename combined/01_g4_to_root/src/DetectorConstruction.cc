#include "DetectorConstruction.hh"
#include "TelescopeSD.hh"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4VisAttributes.hh>

DetectorConstruction::DetectorConstruction() = default;

G4VPhysicalVolume *DetectorConstruction::Construct() {
    fLayers.clear();

    auto *nist = G4NistManager::Instance();
    auto *air = nist->FindOrBuildMaterial("G4_AIR");
    auto *silicon = nist->FindOrBuildMaterial("G4_Si");

    // Dünya hacmi geniş tutuldu; teleskop modülleri ve parçacık saçılmaları için pay bırakıyoruz.
    auto *worldSolid = new G4Box("World", 1.5 * m, 1.5 * m, 1.5 * m);
    auto *worldLogical = new G4LogicalVolume(worldSolid, air, "WorldLogical");
    auto *worldPhysical = new G4PVPlacement(nullptr, {}, worldLogical, "WorldPhysical", nullptr, false, 0, true);

    auto *telescopeSolid = new G4Box("Telescope", 10. * cm, 10. * cm, 1.5 * cm);
    auto *telescopeLogical = new G4LogicalVolume(telescopeSolid, air, "TelescopeLogical");
    new G4PVPlacement(nullptr, {}, telescopeLogical, "TelescopePhysical", worldLogical, false, 0, true);

    const int nLayers = 3;
    const G4double thickness = 0.5 * mm;
    const G4double gap = 0.3 * mm;
    G4double z = -((nLayers - 1) * (thickness + gap)) / 2.0;

    for (int layer = 0; layer < nLayers; ++layer) {
        auto *layerSolid = new G4Box("SensorSolid" + std::to_string(layer), 10. * cm, 10. * cm, 0.5 * thickness);
        auto *layerLogical = new G4LogicalVolume(layerSolid, silicon, "SensorLogical" + std::to_string(layer));
        new G4PVPlacement(nullptr, G4ThreeVector(0., 0., z), layerLogical, "SensorPhysical" + std::to_string(layer),
                          telescopeLogical, false, layer, true);
        layerLogical->SetVisAttributes(G4VisAttributes(G4Colour(0.0, 0.6, 0.8)));
        // Her sensör katmanını daha sonra TelescopeSD içinde indekslemek için saklıyoruz.
        fLayers.push_back(layerLogical);
        z += thickness + gap;
    }

    worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    telescopeLogical->SetVisAttributes(G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.05)));

    return worldPhysical;
}

void DetectorConstruction::ConstructSDandField() {
    auto *sdManager = G4SDManager::GetSDMpointer();
    auto *telescopeSD = new TelescopeSD("TelescopeSD");
    sdManager->AddNewDetector(telescopeSD);

    for (auto *logical : fLayers) {
        // Tüm katmanlar aynı hassas dedektörü paylaşır, hit nesneleri katman id'si içerir.
        SetSensitiveDetector(logical, telescopeSD);
    }
}
