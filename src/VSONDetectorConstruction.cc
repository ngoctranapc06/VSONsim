#include "VSONDetectorConstruction.hh"
#include "VSONNaiSD.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

VSONDetectorConstruction::VSONDetectorConstruction()
{
  DefineMaterials();
}

VSONDetectorConstruction::~VSONDetectorConstruction()
{
  delete Plastic;
  delete Air;
  delete Iron;
  delete NaI;

  delete O;
  delete N;
  delete C;
  delete H;
  delete Na;
  delete I;
}

void VSONDetectorConstruction::DefineMaterials()
{
  //-------------------------------------------------------------------------
  // Materials
  //-------------------------------------------------------------------------

  G4double a, z, density;
  G4int nel;

  H = new G4Element("Hydrogen", "H", z = 1., a = 1.01 * g / mole);
  C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g / mole);
  N = new G4Element("Nitrogen", "N", z = 7., a = 14.01 * g / mole);
  O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);
  Na = new G4Element("Sodium", "Na", z = 11., a = 22.99 * g / mole);
  I = new G4Element("Iodine", "I", z = 53., a = 126.9 * g / mole);

  NaI = new G4Material("NaI", density = 3.67 * g / cm3, nel = 2);
  NaI->AddElement(Na, 1);
  NaI->AddElement(I, 1);

  Air = new G4Material("Air", density = 1.29 * mg / cm3, nel = 2);
  Air->AddElement(N, 70. * perCent);
  Air->AddElement(O, 30. * perCent);

  Plastic = new G4Material("Plastic", density = 1.032 * g / cm3, nel = 2);
  Plastic->AddElement(C, 9);
  Plastic->AddElement(H, 10);

  Iron = new G4Material("Iron", z = 26., a = 55.845 * g / mole, density = 7.86 * g / cm3);
}

G4VPhysicalVolume *VSONDetectorConstruction::Construct()
{
  //-------------------------------------------------------------------------
  // Detector geometry
  //-------------------------------------------------------------------------

  //------------------------------ experimental hall
  G4Box *experimentalHall_box = new G4Box("expHall_b", 3 * m, 3 * m, 3 * m);
  G4LogicalVolume *experimentalHall_log = new G4LogicalVolume(experimentalHall_box, Air, "expHall_L", 0, 0, 0);
  G4VPhysicalVolume *experimentalHall_phys = new G4PVPlacement(0, G4ThreeVector(), experimentalHall_log, "expHall_P",
                                                               0, false, 0);
  experimentalHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  //------------------------------ NaI detectors
  G4VSolid *Naicounter_box = new G4Box("Naicounter_box", 17. * cm / 2, 5.5 * cm / 2, 5.5 * cm / 2);
  //  G4LogicalVolume *Naicounter_log = new G4LogicalVolume(Naicounter_box, Plastic, "Nai_detector", 0, 0, 0);
  G4LogicalVolume *Naicounter_log = new G4LogicalVolume(Naicounter_box, NaI, "Nai_detector", 0, 0, 0);
  G4VPhysicalVolume *Naicounter_phys;

  G4RotationMatrix rm;
  rm.rotateZ(0);

  Naicounter_phys = new G4PVPlacement(G4Transform3D(rm, G4ThreeVector(23.5 * cm, 0, 0)),
                                      Naicounter_log, "Naicounter",
                                      experimentalHall_log, false, 0);

  //------------------------------------------------------------------
  // Sensitive Detector
  //------------------------------------------------------------------

  G4SDManager *SDman = G4SDManager::GetSDMpointer();

  G4String NaiSDname = "/mydet/nai";
  VSONNaiSD *NaiSD = new VSONNaiSD(NaiSDname);
  SDman->AddNewDetector(NaiSD);
  Naicounter_log->SetSensitiveDetector(NaiSD);

  //------------------------------------------------------------------
  // Digitizer modules
  //------------------------------------------------------------------

  return experimentalHall_phys;
}
