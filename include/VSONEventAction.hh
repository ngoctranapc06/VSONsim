#ifndef VSONEventAction_h
#define VSONEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "iostream"
#include "fstream"

class VSONEventAction : public G4UserEventAction
{
  public:
    VSONEventAction(std::ofstream&);
    ~VSONEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
    std::ofstream *output;

  private:
    G4int NaiCollID;
    G4double Edep[2];
};

#endif

    
