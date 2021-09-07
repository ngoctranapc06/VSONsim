#ifndef VSONPrimaryGeneratorAction_h
#define VSONPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4VPrimaryGenerator;
class G4Event;

class VSONPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    VSONPrimaryGeneratorAction();
    ~VSONPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

};

#endif


