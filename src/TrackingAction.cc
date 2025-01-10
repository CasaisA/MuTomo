#include "TrackingAction.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include <format>

TrackingAction::TrackingAction() : G4UserTrackingAction() {

  outFile.open("./output/pirolsmuons.txt", std::ofstream::out | std::ofstream::app);
  // Constructor: can initialize any member variables if necessary
  // outFile << "px0,py0,pz0,x0,y0,z0,px1,py1,pz1,x1,y1,z1" << std::endl;
}

TrackingAction::~TrackingAction() {
  // Destructor: can perform cleanup if necessary
}

void TrackingAction::PreUserTrackingAction(const G4Track *track) {
  // Get the particle name from the track
  G4String particleName = track->GetDefinition()->GetParticleName();

  // If the particle is a muon, print its momentum before interaction
  if (particleName == "mu-" || particleName == "mu+") {
    G4ThreeVector mom = track->GetMomentum();
    G4ThreeVector pos = track->GetPosition();

    // Print momentum to the console
    // std::cout << "Muon (before interaction) momentum: "
    //           << "Px: " << mom.x() << " Py: " << mom.y() << " Pz: " << mom.z()
    //           << std::endl;

    // Optionally, save to a file
    // outFile << "Before interaction - Px: " << mom.x()
    //         << " Py: " << mom.y() << " Pz: " << mom.z()
    //         << std::endl;

    // outFile << mom.x() << "," << mom.y() << "," << mom.z() << "," << pos.x()
    //                     << "," << pos.y() << "," << pos.z();
  }
}

void TrackingAction::PostUserTrackingAction(const G4Track *track) {
  // Get the particle name from the track
  G4String particleName = track->GetDefinition()->GetParticleName();

  // If the particle is a muon, print its momentum after interaction
  if (particleName == "mu-" || particleName == "mu+") {
    G4ThreeVector momentumAfter = track->GetMomentum();

    G4ThreeVector mom = track->GetMomentum();
    G4ThreeVector pos = track->GetPosition();

    // Print momentum to the console
    // std::cout << "Muon (after interaction) momentum: "
    //           << "Px: " << momentumAfter.x() << " Py: " << momentumAfter.y()
    //           << " Pz: " << momentumAfter.z() << std::endl;

    // // Optionally, save to a file
    // outFile << "After interaction - Px: " << momentumAfter.x()
    //         << " Py: " << momentumAfter.y() << " Pz: " << momentumAfter.z()
    //         << std::endl;
    // outFile << mom.x() << "," << mom.y() << "," << mom.z() << "," << pos.x()
    //                     << "," << pos.y() << "," << pos.z() << std::endl;
  }
}
