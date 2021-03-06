#ifndef VSONNaiSD_h
#define VSONNaiSD_h 1

#include "G4VSensitiveDetector.hh"
#include "VSONNaiHit.hh"
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class VSONNaiSD : public G4VSensitiveDetector
{

  public:
      VSONNaiSD(G4String name);
      ~VSONNaiSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);
      void clear();
      void DrawAll();
      void PrintAll();

  private:
      VSONNaiHitsCollection * NaiCollection;
      G4double positionResolution;

};




#endif

