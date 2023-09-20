#ifndef RIGHT_PLATE_SD_H_
#define RIGHT_PLATE_SD_H_

#include "Right_Plate_Hit.hh"
#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class Right_Plate_SD : public G4VSensitiveDetector {
public:
    // Constructor + Destructor
    Right_Plate_SD(G4String name);
    virtual ~Right_Plate_SD();

    virtual void Initialize(G4HCofThisEvent* hce);
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hce);

private:
    Right_Plate_HitsCollection* fRightPlateHitCollection;
};
#endif
