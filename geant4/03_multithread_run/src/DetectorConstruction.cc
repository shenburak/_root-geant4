#include "DetectorConstruction.hh"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4VisAttributes.hh>

#include <string>

DetectorConstruction::DetectorConstruction() = default;

G4VPhysicalVolume *DetectorConstruction::Construct() {
    fLayers.clear();

    auto *nist = G4NistManager::Instance();
    auto *air = nist->FindOrBuildMaterial("G4_AIR");
    auto *scint = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    auto *lead = nist->FindOrBuildMaterial("G4_Pb");

    // Dünya hacmi geniş tutuldu, böylece çok iş parçacıklı çalışmada ışın saçılmaları sınır dışına çıkmıyor.
    auto *worldSolid = new G4Box("WorldSolid", 3. * m, 3. * m, 3. * m);
    auto *worldLogical = new G4LogicalVolume(worldSolid, air, "WorldLogical");
    auto *worldPhysical = new G4PVPlacement(nullptr, {}, worldLogical, "WorldPhysical", nullptr, false, 0, true);

    auto *stackSolid = new G4Box("StackSolid", 20. * cm, 20. * cm, 20. * cm);
    auto *stackLogical = new G4LogicalVolume(stackSolid, air, "StackLogical");
    new G4PVPlacement(nullptr, {}, stackLogical, "StackPhysical", worldLogical, false, 0, true);

    const int nPairs = 4;
    const G4double absorberThickness = 1.5 * cm;
    const G4double scintThickness = 0.8 * cm;
    G4double z = -nPairs * (absorberThickness + scintThickness) / 2.0;

    for (int i = 0; i < nPairs; ++i) {
        auto *absSolid = new G4Box("AbsorberSolid" + std::to_string(i), 20. * cm, 20. * cm, 0.5 * absorberThickness);
        auto *absLogical = new G4LogicalVolume(absSolid, lead, "AbsorberLogical" + std::to_string(i));
        new G4PVPlacement(nullptr, G4ThreeVector(0., 0., z + 0.5 * absorberThickness), absLogical,
                          "AbsorberPhysical" + std::to_string(i), stackLogical, false, 0, true);
        absLogical->SetVisAttributes(G4VisAttributes(G4Colour(0.5, 0.5, 0.5)));
        z += absorberThickness;

        auto *scintSolid =
            new G4Box("ScintSolid" + std::to_string(i), 20. * cm, 20. * cm, 0.5 * scintThickness);
        auto *scintLogical = new G4LogicalVolume(scintSolid, scint, "ScintLogical" + std::to_string(i));
        new G4PVPlacement(nullptr, G4ThreeVector(0., 0., z + 0.5 * scintThickness), scintLogical,
                          "ScintPhysical" + std::to_string(i), stackLogical, false, 0, true);
        scintLogical->SetVisAttributes(G4VisAttributes(G4Colour(0.0, 0.6, 0.2)));
        // Sadece ışıldayıcı katmanlar skorlanacak; bu yüzden pointer'ı saklıyoruz.
        fLayers.push_back(scintLogical);
        z += scintThickness;
    }

    worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
    stackLogical->SetVisAttributes(G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.05)));

    return worldPhysical;
}
