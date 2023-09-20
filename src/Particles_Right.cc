#include "Particles_Right.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void Particles_Right::ReserveRight(const size_t nparticles) {
    posX.reserve(nparticles);
    posY.reserve(nparticles);
    posZ.reserve(nparticles);
    pX.reserve(nparticles);
    pY.reserve(nparticles);
    pZ.reserve(nparticles);
    pX_dir.reserve(nparticles);
    pY_dir.reserve(nparticles);
    pZ_dir.reserve(nparticles);
    pdg_enc.reserve(nparticles);
    trid.reserve(nparticles);
}

//-----------------------------------------------------------------------------

void Particles_Right::ClearVecsRight() {
    posX.clear();
    posY.clear();
    posZ.clear();
    pX.clear();
    pY.clear();
    pZ.clear();
    pX_dir.clear();
    pY_dir.clear();
    pZ_dir.clear();
    pdg_enc.clear();
    trid.clear();
    dummy_right_Track.clear();
    dummy_right_PDG.clear();
    target_right.clear();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
