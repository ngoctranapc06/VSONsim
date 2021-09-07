#include "VSONPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

VSONPrimaryGeneratorAction::VSONPrimaryGeneratorAction()
{

}

VSONPrimaryGeneratorAction::~VSONPrimaryGeneratorAction()
{
}

void VSONPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4int n_particle = 1;
  G4ParticleGun* fParticleGun = new G4ParticleGun(n_particle);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");
  //G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1, 0, 0));
  fParticleGun->SetParticleEnergy(511.*keV);
  //fParticleGun->SetParticleEnergy(1000.*keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
