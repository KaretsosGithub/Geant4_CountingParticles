#include "EventAction.hh"
#include "Analysis.hh"
#include "Particles_Left.hh"
#include "Particles_Right.hh"
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4THitsCollection.hh>
#include <G4UnitsTable.hh>
#include <Randomize.hh>
#include <algorithm>
#include <vector>

using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

EventAction::EventAction()
    : G4UserEventAction()
    , fRightPlateEdepID(-1)
    , fRightPlateCollectionID(-1)
    , fLeftPlateCollectionID(-1) {
    // Constructor
    // Nothing else TODO
}

//-----------------------------------------------------------------------------

EventAction::~EventAction() {
    // Destructor
    // Nothing else TODO
}

//-----------------------------------------------------------------------------

G4THitsMap<G4double>* EventAction::GetHitsCollection(G4int hcID, const G4Event* event) const {
    // Get hit(s) collection for this event
    auto hitsCollection = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

    if (!hitsCollection) {
        G4ExceptionDescription msg;
        msg << "Cannot access hc ID" << hcID;
        G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
    }
    return hitsCollection;
}

//-----------------------------------------------------------------------------

G4double EventAction::EnergySum(G4THitsMap<G4double>* hitsMap) const {
    G4double sum = 0.0;
    // scan the hit(s) collection as any standard std::map<key, value> map
    map<G4int, G4double*>::iterator itr;
    for (itr = hitsMap->GetMap()->begin(); itr != hitsMap->GetMap()->end(); itr++) {
        sum = *(itr->second);
    }
    return sum;
}

//-----------------------------------------------------------------------------

void EventAction::BeginOfEventAction(const G4Event*) {
    fRightPlateEdepID = G4SDManager::GetSDMpointer()->GetCollectionID("Right_Plate_Energy_Detector/Edep");
    fRightPlateCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("Right_Plate_ParticleCollection");

    // We must clear our custom vectors @ the beginning of each event
    fParticles_Right.ClearVecsRight();

    fLeftPlateCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("Left_Plate_ParticleCollection");
    // We must clear our custom vectors @ the beginning of each event
    fParticles_Left.ClearVecsLeft();

    // Also we clear the common stuff vectors.
    common_track.clear();
    common_pdg.clear();
}

//-----------------------------------------------------------------------------

void EventAction::EndOfEventAction(const G4Event* event) {
    // Get hit(s) collections IDs
    if (fRightPlateEdepID < 0) {
        fRightPlateEdepID = G4SDManager::GetSDMpointer()->GetCollectionID("Right_Plate_Energy_Detector/Edep");
        fRightPlateCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("Right_Plate_ParticleCollection");
    }

    if (fLeftPlateCollectionID < 0) {
        fLeftPlateCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("Left_Plate_ParticleCollection");
    }

    Right_Plate_HitsCollection* RightPlateHC = 0;
    Left_Plate_HitsCollection* LeftPlateHC = 0;

    if (event->GetHCofThisEvent()) {
        RightPlateHC = static_cast<Right_Plate_HitsCollection*>(event->GetHCofThisEvent()->GetHC(fRightPlateCollectionID));
        LeftPlateHC = static_cast<Left_Plate_HitsCollection*>(event->GetHCofThisEvent()->GetHC(fLeftPlateCollectionID));
    }

    // This is were we get the data from the HitCollection
    if (RightPlateHC && LeftPlateHC) {

        if (event->GetEventID() % 10000 == 0) {
            G4cout << "+++++++++++++++++++++++++++++++++++++++" << G4endl;
            G4cout << "Number of event :" << event->GetEventID() << G4endl;
            G4cout << "Checkpoint Reached.\n......Please be patient.....Simulation "
                      "running....."
                   << G4endl;
            G4cout << "We got a Right Plate HitCollection with nHits: " << RightPlateHC->entries() << G4endl;
            G4cout << "We got a Left Plate HitCollection with nHits: " << LeftPlateHC->entries() << G4endl;
            G4cout << "+++++++++++++++++++++++++++++++++++++++" << G4endl;
        }

        Fill_The_Vectors(fParticles_Right, fParticles_Left, RightPlateHC, LeftPlateHC);

        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //------------For debugging purposes-------------------
        /*
            cout<<"Number of event "<<event->GetEventID()<<endl;
            for(size_t i=0;i<fParticles_Right.dummy_right_Track.size();i++)
            {
              cout<<"RIGHT plate Track found
           :"<<fParticles_Right.dummy_right_Track[i]; cout<<"  Belongs to PDG ID :
           "<<fParticles_Right.dummy_right_PDG[i]<<endl;
            }
            cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
            for(size_t i=0;i<fParticles_Left.dummy_left_Track.size();i++)
            {
              cout<<"LEFT plate Track found :"<<fParticles_Left.dummy_left_Track[i];
              cout<<"  Belongs to PDG ID :
           "<<fParticles_Left.dummy_left_PDG[i]<<endl;
            }
            cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
            for(size_t i=0;i<common_track.size();i++)
            {
              cout<<"Common Track found :"<<common_track[i]<<"  With PDG ID :
           "<<common_pdg[i]<<endl;
            }
            //------------For debugging purposes-------------------
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        */

        // Energy deposition in the Right Plate
        auto RightPlateEdep = EnergySum(GetHitsCollection(fRightPlateEdepID, event));

        // Fetch the analysis manager
        auto analysisManager = G4AnalysisManager::Instance();

        // Fill histograms with the energy deposited inthe Right plate
        analysisManager->FillH1(0, RightPlateEdep);
        analysisManager->AddNtupleRow(0);
    }
}

//-----------------------------------------------------------------------------

void EventAction::Fill_The_Vectors(Particles_Right& par_right, Particles_Left& par_left,
                                   const Right_Plate_HitsCollection* RightPlateHC, const Left_Plate_HitsCollection* LeftPlateHC) {
    // entries from RIGHT hits collections
    size_t nHits_Right = RightPlateHC->entries();

    // Our custom vectors must be at least nHits long
    par_right.ReserveRight(nHits_Right);

    // Scan the event's RIGHT hits collection and fill our vectors.
    for (size_t i = 0; i < nHits_Right; i++) {
        par_right.trid.push_back((*RightPlateHC)[i]->GetTrId());
        par_right.pdg_enc.push_back((*RightPlateHC)[i]->GetPDGenc());
    }

    //*********************************************************************************************************
    // We create a vector<pair> which contains the TrackID - pdgID information.
    // Then, we use the sort and unique functions, in order to get information
    // only for The unique particles and not all of their steps.
    //*********************************************************************************************************
    transform(par_right.trid.begin(), par_right.trid.end(), par_right.pdg_enc.begin(), back_inserter(par_right.target_right),
              [](int a, int b) {
                  return make_pair(a, b);
              });
    sort(par_right.target_right.begin(), par_right.target_right.end());
    par_right.target_right.erase(unique(par_right.target_right.begin(), par_right.target_right.end()), par_right.target_right.end());

    //*********************************************************************************************************
    //*********************************************************************************************************
    // Next, we break the vector<pair> into two distinct vectors. The
    // dummy_pdg_enc is then forwarded into RunAction into the NTuple.
    for (size_t i = 0; i < par_right.target_right.size(); i++) {
        par_right.dummy_right_Track.push_back(par_right.target_right[i].first);
        par_right.dummy_right_PDG.push_back(par_right.target_right[i].second);
    }

    //*********************************************************************************************************
    //*********************************************************************************************************

    // Scan LEFT hits collection to fill the vectors
    size_t nHits_Left = LeftPlateHC->entries();

    // Our custom vectors must be at least nHits long
    par_left.ReserveLeft(nHits_Left);

    // Scan the event's LEFT hits collection and fill our vectors.
    for (size_t i = 0; i < nHits_Left; i++) {
        par_left.left_pdgID.push_back((*LeftPlateHC)[i]->GetPDGenc());
        par_left.left_trackID.push_back((*LeftPlateHC)[i]->GetTrId());
    }
    //*********************************************************************************************************
    // We create a vector<pair> which contains the TrackID - pdgID information.
    // Then, we use the sort and unique functions, in order to get information
    // only for The unique particles and not all of their steps.
    //*********************************************************************************************************
    transform(par_left.left_trackID.begin(), par_left.left_trackID.end(), par_left.left_pdgID.begin(),
              back_inserter(par_left.target_left), [](int a, int b) {
                  return make_pair(a, b);
              });
    sort(par_left.target_left.begin(), par_left.target_left.end());
    par_left.target_left.erase(unique(par_left.target_left.begin(), par_left.target_left.end()), par_left.target_left.end());
    //*********************************************************************************************************
    //*********************************************************************************************************

    // Next, we break the vector<pair> into two distinct vectors. The
    // dummy_pdg_enc is then forwarded into RunAction into the NTuple.
    for (size_t i = 0; i < par_left.target_left.size(); i++) {
        par_left.dummy_left_Track.push_back(par_left.target_left[i].first);
        par_left.dummy_left_PDG.push_back(par_left.target_left[i].second);
    }

    // *********************************************************************************************************
    // *********************************************************************************************************
    // Common tracks
    for (size_t i = 0; i < par_right.dummy_right_Track.size(); i++) {
        auto track = par_right.dummy_right_Track[i];
        auto pdg = par_right.dummy_right_PDG[i];
        for (size_t j = 0; j < par_left.dummy_left_Track.size(); j++) {
            if (par_left.dummy_left_Track[j] == track) {
                common_track.push_back(track);
                common_pdg.push_back(pdg);
            }
        }
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
