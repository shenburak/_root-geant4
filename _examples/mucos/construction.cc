#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
   G4NistManager  *nist = G4NistManager::Instance();

   // Define World
   //G4Material         *worldMat = nist->FindOrBuildMaterial("G4_AIR");
   G4Material         *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
   G4Box            *solidWorld = new G4Box("solidWorld",0.5*m,0.5*m,0.5*m);
   G4LogicalVolume  *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"logicWorld");
   G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0,0,0), logicWorld,
                                                    "pyhsWorld", 0, false, 0, true);

   // Define copper material using database
   //G4Material* copperMaterial = nist->FindOrBuildMaterial("G4_Cu");

   // Define copper material manually
   G4Element* elCu = new G4Element("copper","Cu",29,63.55*g/mole);
   G4Material* copperMaterial = new G4Material("CU",8.93*g/cm3,1);
   copperMaterial->AddElement(elCu,1);

   // define a block made from copper
   G4Box *solidBlock = new G4Box("solidBlock", 0.2*m, 0.2*m, 5*mm);
   G4LogicalVolume   *logicBlock = new G4LogicalVolume(solidBlock,copperMaterial,"logicBlock");
   G4VPhysicalVolume *physBlock  = new G4PVPlacement(0,G4ThreeVector(0,0,0.25*m),logicBlock,"physBlock",
                                                       logicWorld, false, 0, true);

   // Define detector to save hits (see sensitive detector below)
   G4Box *solidDetector = new G4Box("solidDetector",0.5*m,0.5*m,0.01*m);
   logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicDetector");
   G4VPhysicalVolume *physDetector = new G4PVPlacement(0,G4ThreeVector(0,0,0.5*m),logicDetector,
                                                       "physDetector", logicWorld, false, 0, true);

   return physWorld;
}

void MyDetectorConstruction::ConstructSDandField(){
  MySensitiveDetector *sensDet = new MySensitiveDetector("sensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
}
