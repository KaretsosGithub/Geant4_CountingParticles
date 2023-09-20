#ifndef ROOT_HELPER_HH
#define ROOT_HELPER_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <TH1F.h>

//Print Line Stuff
const int LENGTH = 80;
const char SYMBOL = '-';

using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Function to print a straight line.
void printLine() {
    for (int i = 0; i < LENGTH; i++) {
        cout << SYMBOL;
    }
    cout << endl;
}

//-----------------------------------------------------------------------------

// Function to read a branch from a TTree
vector<int> read_branch(TTree* tree, const string& branch_name) {
    vector<int> branch_contents;
    vector<int>* branch_contents_ptr = nullptr;
    TBranch* branch_ptr = nullptr;
    tree->SetBranchAddress(branch_name.c_str(), &branch_contents_ptr, &branch_ptr);
    // Make sure to call LoadTree before accessing the branch contents
    tree->LoadTree(0);
    // Get the number of entries in the tree
    int num_entries = tree->GetEntries();
    // Loop over all entries and read the branch contents
    for (int i = 0; i < num_entries; i++) {
        branch_ptr->GetEntry(i);
        // Append the contents of the branch to the result vector
        branch_contents.insert(branch_contents.end(), branch_contents_ptr->begin(), branch_contents_ptr->end());
    }
    return branch_contents;
}

//-----------------------------------------------------------------------------

//Function to count the particles/nuclei
void count_particles(const vector<int>& particle_list, unordered_map<int, int>& counts) {
    for (auto particle : particle_list) {
        counts[particle]++;
    }
}

//-----------------------------------------------------------------------------

//Function to print stuff
void print_results(const unordered_map<int, int>& counts) {
    map<int, int> ordered_counts(counts.begin(), counts.end());

    auto elements_counter = 0;   // Counting the total number of all detected nuclei.
    auto nOfParticles = 1000000; // We know that we shot 1 million particles

    //Print the results
    for (auto itr = ordered_counts.begin(); itr != ordered_counts.end(); ++itr)
    {
      auto key = itr->first;
      auto value = itr->second;
      if (key == -14) {
          cout << "Total number of muon-antineutrinos :" << value << endl << endl;
      } else if (key == -13) {
          cout << "Total number of muon+ :" << value << endl << endl;
      } else if (key == -12) {
          cout << "Total number of e-antineutrinos :" << value << endl << endl;
      } else if (key == -11) {
          cout << "Total number of positrons :" << value << endl << endl;
      } else if (key == 11) {
          cout << "Total number of electrons :" << value << endl << endl;
      } else if (key == 12) {
          cout << "Total number of e-neutrinos :" << value << endl << endl;
      } else if (key == 13) {
          cout << "Total number of muon- :" << value << endl << endl;
      } else if (key == 14) {
          cout << "Total number of muon-neutrinos :" << value << endl << endl;
      } else if (key == 22) {
          cout << "Total number of photons :" << value << endl << endl;
      } else if (key == -211) {
          cout << "Total number of pions- :" << value << endl << endl;
      } else if (key == 211) {
          cout << "Total number of pions+ :" << value << endl << endl;
      } else if (key == 111) {
          cout << "Total number of pions0 :" << value << endl << endl;
      } else if (key == 2112) {
          cout << "Total number of neutrons :" << value << endl << endl;
      } else if (key == 2212) {
          cout << "Total number of protons :" << value << endl << endl;
      } else if (key >= 1000010020 && key <= 1000990590) {
          elements_counter = elements_counter + value;
      } else {
          cout << "Unknown error." << endl;
      }
    }
    cout << "Total number of various elements: " << elements_counter << endl;

}

//-----------------------------------------------------------------------------

//Function to create the histograms
void CreateHistograms(TH1F* histograms_array_[])
{
    histograms_array_[0] = new TH1F("histogram 1", "PDG encoding numbers histogram: -14 to +22", 70, -15, 25);
    histograms_array_[1] = new TH1F("histogram 2", "PDG encoding numbers histogram: -211,111,+211", 70, -230, 230);
    histograms_array_[2] = new TH1F("histogram 3", "PDG encoding numbers histogram: 2112 and 2212", 70, 2050, 2250);
    histograms_array_[3] = new TH1F("histogram 4", "PDG encoding numbers histogram: nuclear codes", 111111, 1000000000, 1000300690);
}

//-----------------------------------------------------------------------------

//Function to fill the histograms
void FillHistograms(vector<int>& particles, TH1F* histograms_array[])
{
    for (size_t i = 0; i < particles.size(); i++) {
        int pdg_number = particles.at(i);

        if (pdg_number >= -14 && pdg_number <= 22) {
            histograms_array[0]->Fill(pdg_number);
        } else if (pdg_number == -211 || pdg_number == 211 || pdg_number == 111) {
            histograms_array[1]->Fill(pdg_number);
        } else if (pdg_number == 2112 || pdg_number == 2212) {
            histograms_array[2]->Fill(pdg_number);
        } else {
            histograms_array[3]->Fill(pdg_number);
        }
    }
}

//-----------------------------------------------------------------------------

//Function to draw the histograms
void Draw_histograms(TH1F* histograms_array[]) {

    TCanvas *c = new TCanvas("PDG_encoding_Histograms", "PDG_encoding_Histograms", 100, 0, 1500, 900);
    c->Divide(2, 2);

    for (int i = 0; i < 4; i++) {
        c->cd(i + 1);
        histograms_array[i]->GetXaxis()->SetTitle("PDG_encoding");
        histograms_array[i]->SetFillColor(i + 1);
        histograms_array[i]->SetStats(false);
        histograms_array[i]->Draw();
        if (i == 0) {
            TPaveText* ptext1 = new TPaveText(0.55, 0.65, 0.75, 0.85, "NDC");
            TText* t11 = ptext1->AddText("Pdg encoding numbers");
            TText* t111 = ptext1->AddText("Muon-Antineutrino  --> -14");
            TText* t112 = ptext1->AddText("Muon-Neutrino  --> +14");
            TText* t12 = ptext1->AddText("Muon+  --> -13");
            TText* t13 = ptext1->AddText("Muon-  --> +13");
            TText* t13_1 = ptext1->AddText("Electron-Antineutrino  --> -12");
            TText* t13_2 = ptext1->AddText("Electron-Neutrino  --> +12");
            TText* t14 = ptext1->AddText("Positron  --> -11");
            TText* t15 = ptext1->AddText("Electron  --> +11");
            TText* t16 = ptext1->AddText("Photon  --> 22");
            ptext1->Draw();
        } else if (i == 1) {
            TPaveText* ptext2 = new TPaveText(0.55, 0.65, 0.75, 0.85, "NDC");
            TText* t21 = ptext2->AddText("Pdg encoding numbers:");
            TText* t22 = ptext2->AddText("Pion-  --> -211");
            TText* t211 = ptext2->AddText("Pion 0  --> 111");
            TText* t23 = ptext2->AddText("Pion+  --> +211");
            t22->SetTextColor(kRed);
            t23->SetTextColor(kRed);
            t211->SetTextColor(kRed);
            ptext2->Draw();
        } else if (i == 2) {
            TPaveText* ptext3 = new TPaveText(0.55, 0.65, 0.75, 0.85, "NDC");
            TText* t31 = ptext3->AddText("Pdg encoding numbers:");
            TText* t32 = ptext3->AddText("Neutron  --> +2112");
            TText* t33 = ptext3->AddText("Proton  --> +2212");
            t32->SetTextColor(kGreen);
            t33->SetTextColor(kGreen);
            ptext3->Draw();
        } else {
            TPaveText* ptext4 = new TPaveText(0.55, 0.65, 0.75, 0.85, "NDC");
            TText* t41 = ptext4->AddText("Pdg encoding numbers:");
            TText* t42 = ptext4->AddText("Nuclear codes are given as 10-digit numbers:");
            TText* t43 = ptext4->AddText("+-10L ZZZ AAA I");
            TText* t44 = ptext4->AddText("L : Total number of strange quarks");
            TText* t45 = ptext4->AddText("ZZZ : Atomic number");
            TText* t46 = ptext4->AddText("AAA : Mass number");
            TText* t47 = ptext4->AddText("I : Isomer level");

            t42->SetTextColor(kBlue);
            t43->SetTextColor(kBlue);
            t44->SetTextColor(kBlue);
            t45->SetTextColor(kBlue);
            t46->SetTextColor(kBlue);
            t47->SetTextColor(kBlue);
            ptext4->Draw();

        }
    }
  }
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif
