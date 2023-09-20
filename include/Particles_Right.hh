#ifndef PARTICLES_RIGHT_H_
#define PARTICLES_RIGHT_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

/*Class used for the custom vectors for the
  Right Plate that are used throughtout the
  simulation
*/

class Particles_Right {
public:
    vector<double> posX, posY, posZ;
    vector<double> pX, pY, pZ;
    vector<double> pX_dir, pY_dir, pZ_dir;
    vector<int> pdg_enc, trid;
    vector<int> dummy_right_Track, dummy_right_PDG;
    vector<pair<int, int>> target_right;

    void ReserveRight(const size_t nparticles);
    void ClearVecsRight();
};
#endif
