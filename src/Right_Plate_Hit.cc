#include "Right_Plate_Hit.hh"
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4VisAttributes.hh>

using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

G4ThreadLocal G4Allocator<Right_Plate_Hit>* Right_Plate_HitAllocator = 0;

//-----------------------------------------------------------------------------

Right_Plate_Hit::Right_Plate_Hit()
    : G4VHit()
    ,
    // fMomentum(),
    // fMomentumDir(),
    fTrID()
    , fpdg_enc()

{
    // Constructor
    // Nothing else TODO
}

//-----------------------------------------------------------------------------

Right_Plate_Hit::~Right_Plate_Hit() {
    // Destructor
}

//-----------------------------------------------------------------------------

Right_Plate_Hit::Right_Plate_Hit(const Right_Plate_Hit& right)
    : G4VHit() {
    // fPos = right.fPos;
    // fMomentum = right.fMomentum;
    // fMomentumDir = right.fMomentumDir;
    fTrID = right.fTrID;
    fpdg_enc = right.fpdg_enc;
}

//-----------------------------------------------------------------------------

const Right_Plate_Hit& Right_Plate_Hit::operator=(const Right_Plate_Hit& right) {
    // fPos = right.fPos;
    // fMomentum = right.fMomentum;
    // fMomentumDir = right.fMomentumDir;
    fTrID = right.fTrID;
    fpdg_enc = right.fpdg_enc;

    return *this;
}

//-----------------------------------------------------------------------------

G4bool Right_Plate_Hit::operator==(const Right_Plate_Hit& right) const {
    // Is this == right?return true,else false
    return (this == &right) ? true : false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
