// #include "generator.hh"
// #include "Randomize.hh"

// MyPrimaryGenerator::MyPrimaryGenerator() {
// fParticleGun = new G4ParticleGun(1);
// }

// MyPrimaryGenerator::~MyPrimaryGenerator() { delete fParticleGun; }

// void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
// G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
// G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

// G4double cosTheta;
// do {
// cosTheta = 2 * G4UniformRand() - 1.; // Rango [-1, 1]
// } while (G4UniformRand() >
// std::pow(cosTheta, 2)); // Rechazar valores que no sigan cos^2(theta)

// G4double phi = CLHEP::twopi * G4UniformRand();
// G4double sinTheta = std::sqrt(1. - cosTheta * cosTheta);
// G4double ux = sinTheta * std::cos(phi), uy = sinTheta * std::sin(phi),
// uz = cosTheta;

// auto pos_x = G4UniformRand() * 11.5 * m - 5.75 * m;
// auto pos_y = G4UniformRand() * 11.5 * m - 5.75 * m;
// G4ThreeVector pos(pos_x, pos_y, -18 * m);
// G4ThreeVector mom(0., 0., 1.);

// G4double E_min = 5000 * MeV;
// G4double E_max = 5001 * MeV;

// G4double EnergyMuon = GenerateEnergy(E_min, E_max);

// fParticleGun->SetParticlePosition(pos);
// fParticleGun->SetParticleMomentumDirection(mom);
// fParticleGun->SetParticleEnergy(EnergyMuon);
// fParticleGun->SetParticleDefinition(particle);

// fParticleGun->GeneratePrimaryVertex(anEvent);
// }

// G4double MyPrimaryGenerator::GenerateEnergy(G4double E_min, G4double E_max) {
// G4double r = G4UniformRand();
// return E_max * r + E_min * (1 - r);
// }

#include "generator.hh"

#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

MuonGenerator::MuonGenerator()
    : G4VUserPrimaryGeneratorAction(), fMuonEnergy(100.0 * MeV) {
  fParticleGun = new G4ParticleGun(1);

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *muon = particleTable->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(muon);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(fMuonEnergy);

  fMessenger =
      new G4GenericMessenger(this, "/muonGen/", "Muon Generator Control");
  fMessenger->DeclareMethod("setEnergy", &MuonGenerator::SetMuonEnergy)
      .SetGuidance("Set muon energy in MeV")
      .SetUnit("MeV");
}

MuonGenerator::~MuonGenerator() {
  delete fParticleGun;
  delete fMessenger;
}

void MuonGenerator::GeneratePrimaries(G4Event *anEvent) {

  auto pos_x = G4UniformRand() * 11.5 * m - 5.75 * m;
  auto pos_y = G4UniformRand() * 11.5 * m - 5.75 * m;
  G4ThreeVector pos(pos_x, pos_y, -15 * m);
  G4ThreeVector mom(0., 0., 1.);
  G4double r = G4UniformRand();
  float energia = 6000 * r + 1000 * (1 - r);
  fParticleGun->SetParticleMomentum(energia);
  //fParticleGun->GeneratePrimaryVertex(anEvent);
  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void MuonGenerator::SetMuonEnergy(G4double energy) {fMuonEnergy = energy;}

