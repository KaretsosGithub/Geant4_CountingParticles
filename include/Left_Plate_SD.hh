#ifndef LEFT_PLATE_SD_H_
#define LEFT_PLATE_SD_H_

#include "Left_Plate_Hit.hh"
#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class Left_Plate_SD : public G4VSensitiveDetector {
public:
    // Constructor + Destructor
    Left_Plate_SD(G4String name);
    virtual ~Left_Plate_SD();

    virtual void Initialize(G4HCofThisEvent* hce);
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hce);

private:
    Left_Plate_HitsCollection* fLeftPlateHitCollection;
};
#endif
