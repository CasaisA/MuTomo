#ifndef TrackingAction_h
#define TrackingAction_h

#include "G4UserTrackingAction.hh"
#include <fstream> // For writing to a file
#include <iostream>

class TrackingAction : public G4UserTrackingAction {
public:
    TrackingAction();
    virtual ~TrackingAction();

    // Methods to capture momentum before and after interaction
    virtual void PreUserTrackingAction(const G4Track* track) override;
    virtual void PostUserTrackingAction(const G4Track* track) override;

    std::ofstream outFile;
};

#endif // TrackingAction_h