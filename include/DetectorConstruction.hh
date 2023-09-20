#ifndef DETECTORCONSTRUCTION_H_
#define DETECTORCONSTRUCTION_H_

#include <G4Material.hh>
#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"

class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    // Constructor + Destructor
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    // Field + Sensitive Detectors
    virtual void ConstructSDandField();

    // Uniform electric field stuff
    // We'll build 2 logical volumes with different local fields
    G4LogicalVolume* World_Logical;                // World
    G4LogicalVolume* MotherLogicalVol;             // Mother Volume
    G4LogicalVolume* fElectriclogical_Left_Plate;  // Plate 1 (LEFT Plate)
    G4LogicalVolume* fElectriclogical_Right_Plate; // Plate 2 (Right Plate)
    G4LogicalVolume* fBetween;                     // Volume between  the two plates

    // Setup for the global field
    // It is set to zero.Just to be sure.
    G4ElectricField* pEMfield;
    G4EqMagElectricField* pEquation;
    G4MagIntegratorStepper* pStepper;
    G4FieldManager* pfieldManager;
    G4double pMinStep;
    G4ChordFinder* pChordFinder;

    // Setup for the mother box field
    G4ElectricField* pEMfield_mother_box;
    G4EqMagElectricField* pEquation_mother_box;
    G4MagIntegratorStepper* pStepper_mother_box;
    G4FieldManager* pfieldManager_mother_box;
    G4double pMinStep_mother_box;
    G4ChordFinder* pChordFinder_mother_box;

private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // Let's also check for overlaps between the volumes
    G4bool fCheckOverlaps;
};
#endif
