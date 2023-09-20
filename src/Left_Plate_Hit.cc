#include "Left_Plate_Hit.hh"
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4VisAttributes.hh>

using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

G4ThreadLocal G4Allocator<Left_Plate_Hit>* Left_Plate_HitAllocator = 0;

//-----------------------------------------------------------------------------

Left_Plate_Hit::Left_Plate_Hit()
    : G4VHit()
    ,
    // fLPos(),
    // fLMomentum(),
    // fLMomentumDir(),
    fLpdg_enc()
    , fLTrID()

{
    // Constructor
    // Nothing else TODO
}

//-----------------------------------------------------------------------------

Left_Plate_Hit::~Left_Plate_Hit() {
    // Destructor
}

//-----------------------------------------------------------------------------

Left_Plate_Hit::Left_Plate_Hit(const Left_Plate_Hit& right)
    : G4VHit() {
    // fLPos = right.fLPos;
    // fLMomentum = right.fLMomentum;
    // fLMomentumDir = right.fLMomentumDir;
    fLpdg_enc = right.fLpdg_enc;
    fLTrID = right.fLTrID;
}

//-----------------------------------------------------------------------------

const Left_Plate_Hit& Left_Plate_Hit::operator=(const Left_Plate_Hit& right) {
    // fLPos = right.fLPos;
    // fLMomentum = right.fLMomentum;
    // fLMomentumDir = right.fLMomentumDir;
    fLpdg_enc = right.fLpdg_enc;
    fLTrID = right.fLTrID;

    return *this;
}

//-----------------------------------------------------------------------------

G4bool Left_Plate_Hit::operator==(const Left_Plate_Hit& right) const {
    // Is this == right?return true,else false
    return (this == &right) ? true : false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
