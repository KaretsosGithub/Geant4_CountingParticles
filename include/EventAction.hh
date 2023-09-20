#ifndef EVENTACTION_H_
#define EVENTACTION_H_

#include "Left_Plate_Hit.hh"
#include "Particles_Left.hh"
#include "Particles_Right.hh"
#include "Right_Plate_Hit.hh"
#include <G4SystemOfUnits.hh>
#include <G4THitsMap.hh>
#include <G4UserEventAction.hh>
#include <globals.hh>
#include <unordered_set>
#include <vector>

class EventAction : public G4UserEventAction {
public:
    // Constructor + Destructor
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    Particles_Right fParticles_Right;
    Particles_Left fParticles_Left;

    // Common tracks between the two Plates
    unordered_set<int> common;
    vector<int> common_track;
    vector<int> common_pdg;

private:
    G4THitsMap<G4double>* GetHitsCollection(G4int hcID, const G4Event* event) const;
    G4double EnergySum(G4THitsMap<G4double>* hitsMap) const;
    void Fill_The_Vectors(Particles_Right& par_right, Particles_Left& par_left, const Right_Plate_HitsCollection* RightPlateHC,
                          const Left_Plate_HitsCollection* LeftPlateHC);

    G4int fRightPlateEdepID;       // Right plate energy deposited.
    G4int fRightPlateCollectionID; // Right plate collection
    G4int fLeftPlateCollectionID;  // Left plate collection
};
#endif
