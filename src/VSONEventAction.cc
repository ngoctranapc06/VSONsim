#include "Randomize.hh"

#include "VSONEventAction.hh"

#include "VSONNaiHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

VSONEventAction::VSONEventAction(std::ofstream& tout)
{
  NaiCollID = -1;
  output = &tout;
}

VSONEventAction::~VSONEventAction()
{;}

void VSONEventAction::BeginOfEventAction(const G4Event*)
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  if(NaiCollID<0)
  {
    G4String colNam;
    NaiCollID = SDman->GetCollectionID(colNam="NaiCollection");
  }
}

void VSONEventAction::EndOfEventAction(const G4Event* evt)
{
  if(NaiCollID<0) return;

  Edep[0]=0;

  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  VSONNaiHitsCollection* NHC = 0;
  if(HCE)
  {
    NHC = (VSONNaiHitsCollection*)(HCE->GetHC(NaiCollID));
    int n_hit = NHC->entries();
    for(int i=0; i<n_hit; i++){
      Edep[(*NHC)[i]->GetID()]+=(*NHC)[i]->GetEdep()/keV;
    }
  }

  G4cout<<Edep[0]<<G4endl;
  *output<<Edep[0]<<G4endl;
}
