#include "VSONNaiHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4AttValue.hh"
#include "G4AttDef.hh"
#include "G4AttCheck.hh"

G4Allocator<VSONNaiHit> VSONNaiHitAllocator;

VSONNaiHit::VSONNaiHit()
{;}

VSONNaiHit::~VSONNaiHit()
{;}

VSONNaiHit::VSONNaiHit(const VSONNaiHit &right)
  : G4VHit()
{
  edep = right.edep;
  pos = right.pos;
}

const VSONNaiHit& VSONNaiHit::operator=(const VSONNaiHit &right)
{
  edep = right.edep;
  pos = right.pos;
  return *this;
}

G4int VSONNaiHit::operator==(const VSONNaiHit &right) const
{
  return (this==&right) ? 1 : 0;
}

std::map<G4String,G4AttDef> VSONNaiHit::fAttDefs;

void VSONNaiHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

const std::map<G4String,G4AttDef>* VSONNaiHit::GetAttDefs() const
{
  // G4AttDefs have to have long life.  Use static member...
  if (fAttDefs.empty()) {
    fAttDefs["HitType"] =
      G4AttDef("HitType","Type of hit","Physics","","G4String");
  }
  return &fAttDefs;
}

std::vector<G4AttValue>* VSONNaiHit::CreateAttValues() const
{
  // Create expendable G4AttsValues for picking...
  std::vector<G4AttValue>* attValues = new std::vector<G4AttValue>;
  attValues->push_back
    (G4AttValue("HitType","VSONNaiHit",""));
  //G4cout << "Checking...\n" << G4AttCheck(attValues, GetAttDefs());
  return attValues;
}

void VSONNaiHit::Print()
{;}


