#include "PrimaryGeneratorAction.hh"
#include <G4Box.hh>
#include <G4Exception.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
    , fGun(nullptr) {
    G4int NumberOfParticles = 1;
    G4String particleName;

    fGun = new G4ParticleGun();

    /* Particle Gun initialization.Direction and momentum amp are set with a
       macro.
    */
    auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("proton");
    fGun->SetParticleDefinition(particleDefinition);
    fGun->SetNumberOfParticles(NumberOfParticles);
}

//-----------------------------------------------------------------------------

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    // Destructor
    delete fGun;
}

//-----------------------------------------------------------------------------

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fGun->GeneratePrimaryVertex(anEvent);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
