#ifndef PARTICLES_LEFT_H_
#define PARTICLES_LEFT_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

/*Class used for the custom vectors for the
  Left Plate that are used throughtout the
  simulation
*/

class Particles_Left {
public:
    vector<double> xpos, ypos, zpos;
    vector<double> xp, yp, zp;
    vector<double> xp_dir, yp_dir, zp_dir;
    vector<int> left_pdgID, left_trackID;
    vector<int> dummy_left_Track, dummy_left_PDG;
    vector<pair<int, int>> target_left;

    void ReserveLeft(const size_t nparticles);
    void ClearVecsLeft();
};
#endif
