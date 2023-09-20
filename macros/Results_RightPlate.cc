/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     This script opens the results.root file
     (which contains all the results of the simulation).
     It prints the total number of unique particles that
     can be detected inside the Right Plate. It also draws
     the corresponding histograms, according to the PDG number
     of the detected particles.

     As a reminder, we shot 1 million protons one-by-one
     at a very small angle towards the Right Plate.
     The momentum of the protons is 700MeV/c.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include "root_helper.hh"

const char* kFilename = "results.root";
const char* kOperation = "READ";
const char* kTTreeName = "Two_Plates";
const char* kBranchName = "PDG_encoding_Right";
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int Results_RightPlate() {
    // Open the file with the results
    TFile* f = TFile::Open(kFilename, kOperation);
    if (!f) {
        cerr << "--->ERROR: Could not open file.<---" << endl;
        return 1;
    }

    // Get the tree with the particle data
    TTree* particle_tree = nullptr;
    f->GetObject(kTTreeName, particle_tree);
    if (!particle_tree) {
        cerr << "--->ERROR: Could not get tree.<---" << endl;
        f->Close();
        return 1;
    }

    // Read the particle data from the tree
    vector<int> right_plate_particles = read_branch(particle_tree, kBranchName);

    // Count the particles
    unordered_map<int, int> counts;
    count_particles(right_plate_particles, counts);

    // Print the results
    printLine();
    cout << "Total number of primary particles: 1000000" << endl;
    cout << "Total number of unique particles/nuclei detected inside the Right Plate: " << right_plate_particles.size() << endl;
    printLine();
    cout << "Let's have closer look at the results:" << endl;
    printLine();
    print_results(counts);
    printLine();
    cout << "Check the ROOT canvas for the corresponding histograms!" << endl;
    printLine();

    /*  Create, Fill and
        Draw the histograms */
    TH1F* histograms[4];
    CreateHistograms(histograms);
    FillHistograms(right_plate_particles, histograms);
    Draw_histograms(histograms);

    return 0;
}
