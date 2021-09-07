#include "VSONNaiSD.hh"
#include "VSONNaiHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

VSONNaiSD::VSONNaiSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="NaiCollection");
  positionResolution = 5*cm;
}

VSONNaiSD::~VSONNaiSD(){;}

void VSONNaiSD::Initialize(G4HCofThisEvent*HCE)
{
  static int HCID = -1;
  NaiCollection = new VSONNaiHitsCollection
                   (SensitiveDetectorName,collectionName[0]); 
  if(HCID<0)
  { HCID = GetCollectionID(0); }
  HCE->AddHitsCollection(HCID,NaiCollection);
}

G4bool VSONNaiSD::ProcessHits(G4Step*aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4int detID = aStep->GetPreStepPoint()->GetTouchable()->GetVolume(0)->GetCopyNo();

  if(edep==0.) return true;

  VSONNaiHit* aHit;
  /*
  int nHit = NaiCollection->entries();
  G4ThreeVector hitpos = aStep->GetPreStepPoint()->GetPosition();
  for(int i=0;i<nHit;i++)
  {
    aHit = (*NaiCollection)[i];
    G4ThreeVector pos = aHit->GetPos();
    G4double dist2 = sqr(pos.x()-hitpos.x())
                    +sqr(pos.y()-hitpos.y())+sqr(pos.z()-hitpos.z());
    if(dist2<=sqr(positionResolution))
    aHit->AddEdep(edep);
    return true;
  }
  */
  aHit = new VSONNaiHit();
  aHit->SetEdep( edep );
  aHit->SetID( detID );
  NaiCollection->insert( aHit );

  return true;
}

void VSONNaiSD::EndOfEvent(G4HCofThisEvent*)
{;}

void VSONNaiSD::clear()
{
} 

void VSONNaiSD::DrawAll()
{
} 

void VSONNaiSD::PrintAll()
{
} 

