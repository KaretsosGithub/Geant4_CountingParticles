#ifndef LEFT_PLATE_HIT_H
#define LEFT_PLATE_HIT_H

#include <G4Allocator.hh>
#include <G4THitsCollection.hh>
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include <G4VHit.hh>

using namespace std;

class Left_Plate_Hit : public G4VHit {
public:
    // Constructor+Destructor
    Left_Plate_Hit();
    Left_Plate_Hit(const Left_Plate_Hit& right);
    virtual ~Left_Plate_Hit();

    // Overloaded Operators
    const Left_Plate_Hit& operator=(const Left_Plate_Hit& right);
    G4bool operator==(const Left_Plate_Hit& right) const;
    inline void* operator new(size_t);
    inline void operator delete(void* aHit);

    // Setters and Getters

    /*
    --------------------------------------------------------------------
    Since we are interested in the total number of particles/nuclei
    that can be detected inside the plates, most of the methods in this
    class are not used.
    --------------------------------------------------------------------

    inline void SetPos(G4ThreeVector xyz) { fLPos = xyz; }
    inline G4ThreeVector GetPos() { return fLPos; }

    inline void SetMomentum(G4ThreeVector p_vector) { fLMomentum = p_vector ;}
    inline G4ThreeVector GetMom() { return fLMomentum; }

    inline void SetMomentumDirection(G4ThreeVector p_direction) { fLMomentumDir =
    p_direction ;} inline G4ThreeVector GetMomDir() { return fLMomentumDir; }
    */

    inline void SetTrId(G4int trid) {
        fLTrID = trid;
    }
    inline G4int GetTrId() {
        return fLTrID;
    }

    inline void SetPDGenc(G4int encd) {
        fLpdg_enc = encd;
    }
    inline G4int GetPDGenc() {
        return fLpdg_enc;
    }

private:
    /*
    G4ThreeVector fLPos;          // Position
    G4ThreeVector fLMomentum;     // Momentum
    G4ThreeVector fLMomentumDir;  // Momentum direction
    */

    G4int fLpdg_enc; // PDG encoding
    G4int fLTrID;    // TrackID
};

using Left_Plate_HitsCollection = G4THitsCollection<Left_Plate_Hit>;

extern G4ThreadLocal G4Allocator<Left_Plate_Hit>* Left_Plate_HitAllocator;

/*
  Methods to dynamically arrange the new Hit(s)
  data inside the heap.We also request these methods to be inline
  Of course,the compiler can ignore these requests.
*/

inline void* Left_Plate_Hit::operator new(size_t) {
    if (!Left_Plate_HitAllocator)
        Left_Plate_HitAllocator = new G4Allocator<Left_Plate_Hit>;
    return (void*)Left_Plate_HitAllocator->MallocSingle();
}

inline void Left_Plate_Hit::operator delete(void* aHit) {
    Left_Plate_HitAllocator->FreeSingle((Left_Plate_Hit*)aHit);
}
#endif
