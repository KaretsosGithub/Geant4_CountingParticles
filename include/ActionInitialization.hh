#ifndef ACTIONINITIALIZATION_H_
#define ACTIONINITIALIZATION_H_

#include "DetectorConstruction.hh"
#include <G4VUserActionInitialization.hh>
#include <globals.hh>

class ActionInitialization : public G4VUserActionInitialization {
public:
    // Constructor+Destructor
    ActionInitialization(DetectorConstruction* detConstr);
    virtual ~ActionInitialization();

    virtual void Build() const;
    virtual void BuildForMaster() const;

private:
    DetectorConstruction* fDetectorConstruction;
};
#endif
