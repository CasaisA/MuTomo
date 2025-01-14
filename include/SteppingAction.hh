#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction();
    virtual ~SteppingAction();
    
    virtual void UserSteppingAction(const G4Step* step);

    void SetEventID(G4int id) { eventID = id; }

    void EndOfEventAction();

private:

    std::ofstream outFile;

    G4int eventID;

};

#endif