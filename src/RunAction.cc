#include "RunAction.hh"
#include "Analysis.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include <G4Run.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

RunAction::RunAction(EventAction* eventAction, DetectorConstruction* detCon, PrimaryGeneratorAction* pga)
    : G4UserRunAction()
    , fEventAction(eventAction)
    , fdetCon(detCon)
    , fpga(pga) {

    // Print the event number after each event
    // G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Fetch the analysis Manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Enable ntuple merging in .root format
    if (analysisManager->GetType() == "Root") {
        analysisManager->SetVerboseLevel(0);
        analysisManager->SetFileName("results");
    }

    // Histogram for the energy deposition in the Right Plate
    analysisManager->CreateH1("Edep1", "Energy Deposited in Right Plate", 100, 0., 180. * MeV);

    /* NTuple with the custom information about the nymber of particles
       inside both Plates */

    analysisManager->CreateNtuple("Two_Plates", "Particles Collection");
    // Detected particles inside the Right Plate
    analysisManager->CreateNtupleIColumn("PDG_encoding_Right", fEventAction->fParticles_Right.dummy_right_PDG);
    // Detected particles inside the Left Plate
    analysisManager->CreateNtupleIColumn("PDG_encoding_Left", fEventAction->fParticles_Left.dummy_left_PDG);
    // Common Particles that can be detected inside both plates
    analysisManager->CreateNtupleIColumn("Common_Particles", fEventAction->common_pdg);
    analysisManager->FinishNtuple();
}

//-----------------------------------------------------------------------------

RunAction::~RunAction() {
    // Destructor
    delete G4AnalysisManager::Instance();
}

//-----------------------------------------------------------------------------

void RunAction::BeginOfRunAction(const G4Run*) {

    auto analysisManager = G4AnalysisManager::Instance();
    // The default name is given @ the constructor
    analysisManager->OpenFile();
}

//-----------------------------------------------------------------------------

void RunAction::EndOfRunAction(const G4Run* aRun) {
    auto analysisManager = G4AnalysisManager::Instance();
    G4int n_run = aRun->GetRunID();
    G4cout << "--------------------------------------" << G4endl;
    G4cout << "-->This message is just for your information : run: " << n_run << G4endl;
    G4cout << "--------------------------------------" << G4endl;

    // Save and close the file
    analysisManager->Write();
    analysisManager->CloseFile();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
