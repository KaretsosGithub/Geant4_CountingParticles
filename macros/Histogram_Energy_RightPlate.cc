/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    This script is used to draw the Energy deposition inside
    the Right Plate as a result of the simulation.

    As a reminder, we shot 1 million protons one-by-one
    at a very small angle towards the Right Plate.
    The momentum of the protons is 700MeV/c.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>

// Root file with the results
const char* kFilename = "results.root";
// Name of the Energy histogram inside the results
const char* kHistname = "Edep1";

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Function read the .root file and fetch the TH1D histogram.
void displayHistogram(const char* filename, const char* histname) {
    TCanvas* c = new TCanvas("Energy_Histogram_Right_Plate", "Energy_Histogram_Right_Plate", 100, 0, 900, 600);

    // Root file with the results
    TFile* file = new TFile(filename);

    // Fetch histogram from the file
    TH1D* hist = (TH1D*)file->Get(histname);

    // File dows not exist/is corrupted
    if (!file || file->IsZombie()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    if (!hist) {
        cerr << "Error: Could not get histogram " << histname << " from file " << filename << endl;
        file->Close();
        return;
    }
    c->cd();
    hist->SetTitle("Energy Deposited Inside the Right Plate");
    hist->SetStats(false);
    hist->GetXaxis()->SetTitle("Energy Deposited (MeV)");
    hist->SetMarkerStyle(kFullCircle);
    hist->SetMarkerColor(9);
    hist->SetMarkerSize(0.8);
    hist->Draw();
}

//-----------------------------------------------------------------------------

// Main function
int Histogram_Energy_RightPlate() {
    displayHistogram(kFilename, kHistname);
    return 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
