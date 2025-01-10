#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  // Get the NIST Material Manager
  G4NistManager *nist = G4NistManager::Instance();
  // Define Elements
  G4Element *elSi = nist->FindOrBuildElement("Si");
  G4Element *elO = nist->FindOrBuildElement("O");
  G4Element *elAl = nist->FindOrBuildElement("Al");
  G4Element *elFe = nist->FindOrBuildElement("Fe");

  // Define Standard Rock
  G4Material *StandardRock = new G4Material("StandardRock", 2.65 * g / cm3, 4);
  StandardRock->AddElement(elSi, 48 * perCent);
  StandardRock->AddElement(elO, 46 * perCent);
  StandardRock->AddElement(elAl, 3.5 * perCent);
  StandardRock->AddElement(elFe, 2.5 * perCent);
  // Define Base Material (SiO2 - Quartz)
  G4Material *SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  // Define Air (Low Density Material)
  G4Material *air = nist->FindOrBuildMaterial("G4_AIR");

  // Define Water
  G4Material *water = nist->FindOrBuildMaterial("G4_NAPHTHALENE");
  water = nist->FindOrBuildMaterial("G4_WATER");

  // Define Porous Material as a Mixture
  float sio_frac = 0.6;
  float water_frac = .2 * (1 - sio_frac);
  float air_frac = 1 - sio_frac - water_frac;

  G4double density = sio_frac * StandardRock->GetDensity() +
                     air_frac * air->GetDensity() +
                     water_frac * water->GetDensity();
  printf("Density %f \n", density / g * cm3);
  G4Material *porousSiO2 = new G4Material("Porous_SiO2", density,
                                          3); // 3 components: SiO2, Air, Water

  porousSiO2->AddMaterial(StandardRock, sio_frac);
  porousSiO2->AddMaterial(air, air_frac);
  porousSiO2->AddMaterial(water, water_frac);
  // porousSiO2 = StandardRock;

  // Define World Volume (Vacuum or Air)
  G4double worldSize = 15 * m;
  G4Material *worldMaterial = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld =
      new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);
  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld, worldMaterial, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(
      nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

  // Define Gruyère-like Solid Volume
  G4double boxSize = 15 * m;
  G4Box *solidSample =
      new G4Box("PorousSolid", boxSize / 2, boxSize / 2, 10 * m / 2);
  G4LogicalVolume *logicSample =
      new G4LogicalVolume(solidSample, porousSiO2, "PorousSolid");

  // Place Porous Solid in the World
  new G4PVPlacement(nullptr, G4ThreeVector(), logicSample, "PorousSolid",
                    logicWorld, false, 0, true);

  // Visualization Attributes
  G4VisAttributes *visAttributes = new G4VisAttributes(
      G4Colour(1.0, 0.8, 0.6, 0.5)); // Light brown, semi-transparent
  visAttributes->SetForceSolid(true);
  logicSample->SetVisAttributes(visAttributes);

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
  // MySensitiveDetector *sensDet = new
  // MySensitiveDetector("SensitiveDetector");

  // logicDetector->SetSensitiveDetector(sensDet);
}
