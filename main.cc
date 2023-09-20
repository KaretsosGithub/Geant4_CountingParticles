/* Main function for the Geant4
   simulation */

#ifdef G4MULTITHREADED
#    include <G4MTRunManager.hh>
#else
#    include <G4RunManager.hh>
#endif
#include "ActionInitialization.hh"
#include "Analysis.hh"
#include "DetectorConstruction.hh"
#include <G4EmStandardPhysics_option4.hh>
#include <G4OpticalPhysics.hh>
#include <G4String.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <vector>
// We will use a reference physics list
#include <QGSP_BERT.hh>

using namespace std;

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

int main(int argc, char** argv) {
    cout << "-----------------------------------\n";
    cout << "Brace yourself Random User........." << endl;
    cout << "Application starting..." << endl;
    cout << "-----------------------------------\n";

    // Instantiate G4UIExecutive if there are no arguments (interactive mode)
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Construct the default run manager
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
#else
    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4Random::setTheSeed(100);
    G4RunManager* runManager = new G4RunManager;
#endif

    // Mandarory classes
    //---------------------------------------------------------------------
    // Detector construction
    auto detConstruction = new DetectorConstruction();
    runManager->SetUserInitialization(detConstruction);

    // Physics list
    G4VModularPhysicsList* physicsList = new QGSP_BERT;
    physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
    runManager->SetUserInitialization(physicsList);

    // User action initialization
    auto actionInit = new ActionInitialization(detConstruction);
    runManager->SetUserInitialization(actionInit);
    //---------------------------------------------------------------------

    // Initialize G4 kernel
    runManager->Initialize();

    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (!ui) // batch mode
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // interactive mode : define UI session
        UImanager->ApplyCommand("/control/execute vis.mac");
        if (ui->IsGUI()) {
            UImanager->ApplyCommand("/control/execute gui.mac");
        }
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    delete visManager;
    delete runManager;

    cout << "-----------------------------------\n";
    cout << "Congratulations!\n";
    cout << "Application successfully ended.\nSee you Soon :-))" << endl;
    cout << "-----------------------------------\n";

    return 0;
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
