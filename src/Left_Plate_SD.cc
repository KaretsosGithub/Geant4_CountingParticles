#include "Left_Plate_SD.hh"
#include "Analysis.hh"
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4Track.hh>
#include <G4VProcess.hh>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

Left_Plate_SD::Left_Plate_SD(G4String name)
    : G4VSensitiveDetector(name)
    , fLeftPlateHitCollection(0) {
    // Constructor
    G4String HCname;
    collectionName.insert(HCname = "Left_Plate_ParticleCollection");
}

//-----------------------------------------------------------------------------

Left_Plate_SD::~Left_Plate_SD() {
    // Destructor
}

//-----------------------------------------------------------------------------

void Left_Plate_SD::Initialize(G4HCofThisEvent* hce) {
    // This function if called @ the start of each event
    fLeftPlateHitCollection = new Left_Plate_HitsCollection(SensitiveDetectorName, collectionName[0]);

    static G4int hcid = -1;
    if (hcid < 0) {
        hcid = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }

    hce->AddHitsCollection(hcid, fLeftPlateHitCollection);
}

//-----------------------------------------------------------------------------

G4bool Left_Plate_SD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {

    G4Track* theTrack = aStep->GetTrack();

    auto particlePDG = theTrack->GetParticleDefinition()->GetPDGEncoding();
    auto TrackID = theTrack->GetTrackID();

    // Let's create a hit
    auto newHit = new Left_Plate_Hit;

    // Now,let's interrogate the hit(from this step) for information
    newHit->SetPDGenc(particlePDG);
    newHit->SetTrId(TrackID);

    // Insert the hit in the collection
    fLeftPlateHitCollection->insert(newHit);

    return true;
}

//-----------------------------------------------------------------------------

void Left_Plate_SD::EndOfEvent(G4HCofThisEvent*) {
    // Nothing else TODO
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
