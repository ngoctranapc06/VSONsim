#ifndef VSONNaiHit_h
#define VSONNaiHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class G4AttDef;

class VSONNaiHit : public G4VHit
{
  public:

      VSONNaiHit();
      ~VSONNaiHit();
      VSONNaiHit(const VSONNaiHit &right);
      const VSONNaiHit& operator=(const VSONNaiHit &right);
      G4int operator==(const VSONNaiHit &right) const;


      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      const std::map<G4String,G4AttDef>* GetAttDefs() const;
      std::vector<G4AttValue>* CreateAttValues() const;
      void Print();

  private:
      G4double edep;
      G4int detID;
      G4ThreeVector pos;
      static std::map<G4String,G4AttDef> fAttDefs;

  public:
      inline void SetEdep(G4double de)
      { edep = de; }
      inline void AddEdep(G4double de)
      { edep += de; }
      inline G4double GetEdep()
      { return edep; }


      inline void SetID(G4int id)
      { detID = id; }
      inline G4int GetID()
      { return detID; }


};

typedef G4THitsCollection<VSONNaiHit> VSONNaiHitsCollection;

extern G4Allocator<VSONNaiHit> VSONNaiHitAllocator;

inline void* VSONNaiHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) VSONNaiHitAllocator.MallocSingle();
  return aHit;
}

inline void VSONNaiHit::operator delete(void *aHit)
{
  VSONNaiHitAllocator.FreeSingle((VSONNaiHit*) aHit);
}

#endif


