#include "Particles_Left.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void Particles_Left::ReserveLeft(const size_t nparticles) {
    xpos.reserve(nparticles);
    ypos.reserve(nparticles);
    zpos.reserve(nparticles);
    xp.reserve(nparticles);
    yp.reserve(nparticles);
    zp.reserve(nparticles);
    xp_dir.reserve(nparticles);
    yp_dir.reserve(nparticles);
    zp_dir.reserve(nparticles);
    left_pdgID.reserve(nparticles);
    left_trackID.reserve(nparticles);
}

//-----------------------------------------------------------------------------

void Particles_Left::ClearVecsLeft() {
    xpos.clear();
    ypos.clear();
    zpos.clear();
    xp.clear();
    yp.clear();
    zp.clear();
    xp_dir.clear();
    yp_dir.clear();
    zp_dir.clear();
    left_pdgID.clear();
    left_trackID.clear();
    dummy_left_Track.clear();
    dummy_left_PDG.clear();
    target_left.clear();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
