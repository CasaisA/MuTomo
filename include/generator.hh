#ifndef MUON_GENERATOR_HH
#define MUON_GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

class MuonGenerator : public G4VUserPrimaryGeneratorAction {
public:
    MuonGenerator();
    ~MuonGenerator() override;

    void GeneratePrimaries(G4Event* anEvent) override;
    void SetMuonEnergy(G4double energy);

private:
    G4ParticleGun* fParticleGun;
    G4double fMuonEnergy;
    G4GenericMessenger* fMessenger;
};

#endif // MUON_GENERATOR_HH