#ifndef PRIMARYGENERATORACTION_H_
#define PRIMARYGENERATORACTION_H_

#include <G4VUserPrimaryGeneratorAction.hh>
#include <globals.hh>

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    // Constructor+Destructor
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

private:
    G4ParticleGun* fGun;
};
#endif
