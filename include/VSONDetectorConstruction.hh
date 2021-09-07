#ifndef VSONDetectorConstruction_h
#define VSONDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4Material;
class G4Element;

class VSONDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    VSONDetectorConstruction();
    ~VSONDetectorConstruction();

  public:
     G4VPhysicalVolume* Construct();

  private:
     void DefineMaterials();

  G4Material* Air;
  G4Material* Plastic;
  G4Material* Iron;
  G4Material* NaI;

  G4Element* H;
  G4Element* C;
  G4Element* N;
  G4Element* O;
  G4Element* Na;
  G4Element* I;

};

#endif
