#include "SteppingAction.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4OpticalPhoton.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include <cmath> // For M_PI
#include <string>

SteppingAction::SteppingAction() {
  // Open a file to save the energies of the photons
  outFile.open("./output/muons.txt", std::ofstream::out | std::ofstream::app);
  outFile << "px0,py0,pz0,x0,y0,z0,px1,py1,pz1,x1,y1,z1" << std::endl;
}

// Create destructor
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step *step) {
  // Define what we do at each step
  auto track = step->GetTrack();

  G4String particleName = track->GetDefinition()->GetParticleName();
  auto particle = track->GetParticleDefinition();
  auto volume = track->GetVolume();
  G4StepPoint *preStepPoint = step->GetPreStepPoint();
  G4StepPoint *postStepPoint = step->GetPostStepPoint();

  G4LogicalVolume *preVolume =
      preStepPoint->GetPhysicalVolume()
          ? preStepPoint->GetPhysicalVolume()->GetLogicalVolume()
          : nullptr;
  G4LogicalVolume *postVolume =
      postStepPoint->GetPhysicalVolume()
          ? postStepPoint->GetPhysicalVolume()->GetLogicalVolume()
          : nullptr;
  G4LogicalVolume *thisVolume =
      track->GetVolume() ? track->GetVolume()->GetLogicalVolume() : nullptr;

  G4ThreeVector mom = track->GetMomentum();
  G4ThreeVector pos = track->GetPosition();
  bool muon = (particleName == "mu-" && track->GetParentID() == 0);
  bool to_kill = (track->GetTrackStatus() == fKillTrackAndSecondaries ||
            track->GetTrackStatus() == fStopAndKill);
  bool saved_output = false;
  if (!muon)
    return;
  if (track->GetCurrentStepNumber() == 1 && !to_kill ) {
    auto e = track->GetVertexKineticEnergy();
    auto p = sqrt(pow(e + 105*MeV, 2)  - pow(105 * MeV, 2));

    G4ThreeVector initialMomentum = track->GetVertexMomentumDirection() * p;
    mom = initialMomentum;
    // outFile << std::endl;
    outFile << mom.x() << "," << mom.y() << "," << mom.z() << "," << pos.x()
            << "," << pos.y() << "," << pos.z() << ",";
    G4String particleName = track->GetDefinition()->GetParticleName();
  }

  else if ( to_kill &&
           thisVolume->GetName() == "LogicBoxWithHole") {
    outFile << "nan,nan,nan,nan,nan,nan" << std::endl;
  } else if (to_kill) {
    outFile << mom.x() << "," << mom.y() << "," << mom.z() << "," << pos.x()
            << "," << pos.y() << "," << pos.z() << std::endl;
    saved_output = true;
  }
}

void SteppingAction::EndOfEventAction() {}