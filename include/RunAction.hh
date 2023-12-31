#ifndef RUNACTION_H_
#define RUNACTION_H_

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include <G4UserRunAction.hh>
#include <globals.hh>

class G4Run;

class RunAction : public G4UserRunAction {
public:
    // Constructor+Destructor
    RunAction(EventAction* eventAction, DetectorConstruction* detCon, PrimaryGeneratorAction* pga);
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    EventAction* fEventAction;
    DetectorConstruction* fdetCon;
    PrimaryGeneratorAction* fpga;
};
#endif
