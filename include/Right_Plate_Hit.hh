#ifndef RIGHT_PLATE_HIT_H
#define RIGHT_PLATE_HIT_H

#include <G4Allocator.hh>
#include <G4THitsCollection.hh>
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include <G4VHit.hh>

using namespace std;

class Right_Plate_Hit : public G4VHit {
public:
    // Constructor+Destructor
    Right_Plate_Hit();
    Right_Plate_Hit(const Right_Plate_Hit& right);
    virtual ~Right_Plate_Hit();

    // Overloaded Operators
    const Right_Plate_Hit& operator=(const Right_Plate_Hit& right);
    G4bool operator==(const Right_Plate_Hit& right) const;
    inline void* operator new(size_t);
    inline void operator delete(void* aHit);

    // Setters and Getters
    /*
    --------------------------------------------------------------------
    Since we are interested in the total number of particles/nuclei
    that can be detected inside the plates, most of the methods in this
    class are not used.
    --------------------------------------------------------------------
    inline void SetPos(G4ThreeVector pos_vector) { fPos = pos_vector; }
    inline G4ThreeVector GetPos() { return fPos; }

    inline void SetMomentum(G4ThreeVector mom_vector) { fMomentum = mom_vector ;}
    inline G4ThreeVector GetMom() { return fMomentum; }

    inline void SetMomentumDirection(G4ThreeVector mom_direction) { fMomentumDir =
    mom_direction ;} inline G4ThreeVector GetMomDir() { return fMomentumDir; }
    */

    inline void SetPDGenc(G4int enc) {
        fpdg_enc = enc;
    }
    inline G4int GetPDGenc() {
        return fpdg_enc;
    }

    inline void SetTrId(G4int tid) {
        fTrID = tid;
    }
    inline G4int GetTrId() {
        return fTrID;
    }

private:
    /*
    G4ThreeVector fPos;          // Position
    G4ThreeVector fMomentum;     // Momentum
    G4ThreeVector fMomentumDir;  // Momentum direction
    */

    G4int fTrID;    // TrackID
    G4int fpdg_enc; // PDG encoding
};

using Right_Plate_HitsCollection = G4THitsCollection<Right_Plate_Hit>;

extern G4ThreadLocal G4Allocator<Right_Plate_Hit>* Right_Plate_HitAllocator;

/*
  Methods to dynamically arrange the new Hit(s)
  data inside the heap.We also request these methods to be inline
  Of course,the compiler can ignore these requests.
*/

inline void* Right_Plate_Hit::operator new(size_t) {
    if (!Right_Plate_HitAllocator)
        Right_Plate_HitAllocator = new G4Allocator<Right_Plate_Hit>;
    return (void*)Right_Plate_HitAllocator->MallocSingle();
}

inline void Right_Plate_Hit::operator delete(void* aHit) {
    Right_Plate_HitAllocator->FreeSingle((Right_Plate_Hit*)aHit);
}
#endif
