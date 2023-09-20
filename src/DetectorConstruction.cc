#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"
#include "G4EqMagElectricField.hh"
#include "G4EquationOfMotion.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4NistManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VisAttributes.hh"
#include "Left_Plate_SD.hh"
#include "Right_Plate_SD.hh"

using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
    , World_Logical(nullptr)
    , fElectriclogical_Left_Plate(nullptr)
    , fElectriclogical_Right_Plate(nullptr)
    , fBetween(0)
    , pEMfield(0)
    , pEquation(0)
    , pStepper(0)
    , pfieldManager(0)
    , pMinStep(0)
    , pChordFinder(0)
    , pEMfield_mother_box(0)
    , pEquation_mother_box(0)
    , pStepper_mother_box(0)
    , pfieldManager_mother_box(0)
    , pMinStep_mother_box(0)
    , pChordFinder_mother_box(0)
    , fCheckOverlaps(true) {
    // Constructor
    // Nothing else TODO
}

//-----------------------------------------------------------------------------

DetectorConstruction::~DetectorConstruction() {
    // Destructor
    // Nothing else TODO
}

//-----------------------------------------------------------------------------

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Define the materials
    DefineMaterials();

    // Define volumes and return the physical volume
    return DefineVolumes();
}

//-----------------------------------------------------------------------------

void DetectorConstruction::DefineMaterials() {
    auto nistManager = G4NistManager::Instance();

    // The world is vacuum
    nistManager->FindOrBuildMaterial("G4_Galactic");
    // The two plates are made of aluminum 6061.
    // We need to build it, before using it.
    nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_Mg");
    nistManager->FindOrBuildMaterial("G4_Si");
    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Cu");
    nistManager->FindOrBuildMaterial("G4_Cr");
    nistManager->FindOrBuildMaterial("G4_Zn");
    nistManager->FindOrBuildMaterial("G4_Ti");
    nistManager->FindOrBuildMaterial("G4_Mn");

    // Let's print the materials table
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//-----------------------------------------------------------------------------

G4VPhysicalVolume* DetectorConstruction::DefineVolumes() {
    // Get materials
    auto worldmaterial = G4Material::GetMaterial("G4_Galactic");
    // Fetch aluminum 6061 materials
    auto mat_1 = G4Material::GetMaterial("G4_Al");
    auto mat_2 = G4Material::GetMaterial("G4_Mg");
    auto mat_3 = G4Material::GetMaterial("G4_Si");
    auto mat_4 = G4Material::GetMaterial("G4_Fe");
    auto mat_5 = G4Material::GetMaterial("G4_Cu");
    auto mat_6 = G4Material::GetMaterial("G4_Cr");
    auto mat_7 = G4Material::GetMaterial("G4_Zn");
    auto mat_8 = G4Material::GetMaterial("G4_Ti");
    auto mat_9 = G4Material::GetMaterial("G4_Mn");

    G4String name;
    G4double density, fractionmass;
    G4int ncomponents;

    // Building process of aluminum 6061
    density = 2.7 * g / cm3;
    auto SteelPlateMaterial = new G4Material(name = "Aluminun_6061", density, ncomponents = 9);
    SteelPlateMaterial->AddMaterial(mat_1, fractionmass = 96.11 * perCent);
    SteelPlateMaterial->AddMaterial(mat_2, fractionmass = 1.18 * perCent);
    SteelPlateMaterial->AddMaterial(mat_3, fractionmass = 0.78 * perCent);
    SteelPlateMaterial->AddMaterial(mat_4, fractionmass = 0.68 * perCent);
    SteelPlateMaterial->AddMaterial(mat_5, fractionmass = 0.39 * perCent);
    SteelPlateMaterial->AddMaterial(mat_6, fractionmass = 0.34 * perCent);
    SteelPlateMaterial->AddMaterial(mat_7, fractionmass = 0.24 * perCent);
    SteelPlateMaterial->AddMaterial(mat_8, fractionmass = 0.14 * perCent);
    SteelPlateMaterial->AddMaterial(mat_9, fractionmass = 0.14 * perCent);

    // Envelope parameters
    G4double env_sizeXY = 100. * cm;
    G4double env_sizeZ = 100. * cm;

    // World dimension
    G4double worldsizeXY = 20.5 * env_sizeXY;
    G4double worldsizeZ = 20.3 * env_sizeZ;

    // The two plates dimensions
    G4double box_X = 600. * cm;
    G4double box_Y = 20. * cm;
    G4double box_Z = 5. * cm;

    // Gap between the two plates
    G4double dummy_box_X = 600. * cm;
    G4double dummy_box_Y = 20. * cm;
    G4double dummy_box_Z = 4. * cm;

    G4double MotherBox_X = 600. * cm;
    G4double MotherBox_Y = 20. * cm;
    G4double MotherBox_Z = 14. * cm;

    // Let's create the "World"
    auto WorldBox = new G4Box("World", worldsizeXY / 2, worldsizeXY / 2, worldsizeZ / 2);
    World_Logical = new G4LogicalVolume(WorldBox, worldmaterial, "World");
    auto physWorld = new G4PVPlacement(0, G4ThreeVector(), World_Logical, "World", 0, false, 0, fCheckOverlaps);

    // Let's create the mother volume.
    // The two aluminun 6061 plates as well as the "gap"
    // volume are placed in there.
    auto motherBox = new G4Box("motherBox", MotherBox_X / 2, MotherBox_Y / 2, MotherBox_Z / 2);
    MotherLogicalVol = new G4LogicalVolume(motherBox, worldmaterial, "MotherLog");
    new G4PVPlacement(0, G4ThreeVector(150. * cm, 0. * cm, 0. * cm), MotherLogicalVol, "MotherLogicalVol", World_Logical, false, 0,
                      fCheckOverlaps);

    // LEFT plate
    auto LeftPlate = new G4Box("LeftPlate", box_X / 2, box_Y / 2, box_Z / 2);
    fElectriclogical_Left_Plate = new G4LogicalVolume(LeftPlate, SteelPlateMaterial, "LeftPlateLV");
    new G4PVPlacement(0, G4ThreeVector(0. * cm, 0. * cm, -4.5 * cm), fElectriclogical_Left_Plate, "LeftPlateLV", MotherLogicalVol,
                      false, 0, fCheckOverlaps);

    // Gap Volume between the two plates
    auto Between = new G4Box("Between", dummy_box_X / 2, dummy_box_Y / 2, dummy_box_Z / 2);
    fBetween = new G4LogicalVolume(Between, worldmaterial, "BetweenLV");
    new G4PVPlacement(0, G4ThreeVector(0. * cm, 0. * cm, 0. * cm), fBetween, "BetweenLV", MotherLogicalVol, false, 0, fCheckOverlaps);

    // RIGHT plate
    auto RightPlate = new G4Box("RightPlate", box_X / 2, box_Y / 2, box_Z / 2);
    fElectriclogical_Right_Plate = new G4LogicalVolume(RightPlate, SteelPlateMaterial, "RightPlateLV");
    new G4PVPlacement(0, G4ThreeVector(0. * cm, 0. * cm, 4.5 * cm), fElectriclogical_Right_Plate, "RightPlateLV", MotherLogicalVol,
                      false, 0, fCheckOverlaps);

    //--------------------
    // Visual VisAttributes
    //--------------------
    //-----------------------------------------------------------
    //
    // World
    World_Logical->SetVisAttributes(G4VisAttributes::GetInvisible());

    auto color = new G4VisAttributes(G4Colour::Green());
    auto color2 = new G4VisAttributes(G4Colour::Blue());

    // Left plate
    fElectriclogical_Left_Plate->SetVisAttributes(color);
    color->SetVisibility(true);
    color->SetForceSolid(true);
    // Gap Volume, between the two plates
    fBetween->SetVisAttributes(color2);
    color2->SetVisibility(true);
    color2->SetForceSolid(false);
    // Right plate
    fElectriclogical_Right_Plate->SetVisAttributes(color);
    color->SetVisibility(true);
    color->SetForceSolid(false);
    //-----------------------------------------------------------
    //--------------------

    // Let's print the materials Table
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    // Always return the physical world
    return physWorld;
}

//-----------------------------------------------------------------------------

void DetectorConstruction::ConstructSDandField() {
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    // The world field. It is set to 0, just to be sure
    //--------------------------------------------------
    pEMfield = new G4UniformElectricField(G4ThreeVector(0.0 * kilovolt / m, 0.0 * kilovolt / m, 0.0 * kilovolt / m));
    // Create an equation of motion for this field
    pEquation = new G4EqMagElectricField(pEMfield);

    G4int nvar = 8;
    pStepper = new G4ClassicalRK4(pEquation, nvar);

    // Get the global field manager
    pfieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    // Set this field to the global field manager
    pfieldManager->SetDetectorField(pEMfield, false);

    pMinStep = 0.010 * mm; // minimal step of 10 microns

    // The driver will ensure that integration is control to give
    // acceptable integration error
    auto pIntgrationDriver = new G4MagInt_Driver(pMinStep, pStepper, pStepper->GetNumberOfVariables());
    pChordFinder = new G4ChordFinder(pIntgrationDriver);
    pfieldManager->SetChordFinder(pChordFinder);
    //--------------------------------------------------
    //--------------------------------------------------

    // MotherBox local field.This field is set to 4500kV/m and it is pushed inside
    // all daughter volumes
    //--------------------------------------------------
    pEMfield_mother_box = new G4UniformElectricField(G4ThreeVector(0.0 * kilovolt / m, 0.0 * kilovolt / m, 4500.0 * kilovolt / m));
    // Create an equation of motion for this field
    pEquation_mother_box = new G4EqMagElectricField(pEMfield_mother_box);

    G4int nvar_mother_box = 8;
    pStepper_mother_box = new G4ClassicalRK4(pEquation_mother_box, nvar_mother_box);

    // Get the local field manager
    pfieldManager_mother_box = new G4FieldManager(pEMfield_mother_box);
    MotherLogicalVol->SetFieldManager(pfieldManager_mother_box, true);

    pMinStep_mother_box = 0.010 * mm; // minimal step of 10 microns

    // The driver will ensure that integration is control to give
    // acceptable integration error
    auto pIntgrationDriver_mother_box =
        new G4MagInt_Driver(pMinStep_mother_box, pStepper_mother_box, pStepper_mother_box->GetNumberOfVariables());
    pChordFinder_mother_box = new G4ChordFinder(pIntgrationDriver_mother_box);
    pfieldManager_mother_box->SetChordFinder(pChordFinder_mother_box);
    //--------------------------------------------------
    //--------------------------------------------------

    // We need to declare the two Aluminun_6061 plates as sensitive detectors
    // in order to get various information.
    //--------------------------------------------------

    // Energy information. Might not be used.
    auto Right_Plate_Energy_Detector = new G4MultiFunctionalDetector("Right_Plate_Energy_Detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(Right_Plate_Energy_Detector);
    G4VPrimitiveScorer* primitive;
    primitive = new G4PSEnergyDeposit("Edep");
    Right_Plate_Energy_Detector->RegisterPrimitive(primitive);
    SetSensitiveDetector("RightPlateLV", Right_Plate_Energy_Detector);

    // Right Plate custom information
    Right_Plate_SD* Right_Plate_Custom_Detector = new Right_Plate_SD("Right_Plate_Custom_Detector");

    G4SDManager::GetSDMpointer()->AddNewDetector(Right_Plate_Custom_Detector);
    SetSensitiveDetector("RightPlateLV", Right_Plate_Custom_Detector);

    // Left Plate custom information
    Left_Plate_SD* Left_Plate_Custom_Detector = new Left_Plate_SD("Left_Plate_Custom_Detector");

    G4SDManager::GetSDMpointer()->AddNewDetector(Left_Plate_Custom_Detector);
    SetSensitiveDetector("LeftPlateLV", Left_Plate_Custom_Detector);
    //----------------------------------------------------------
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
