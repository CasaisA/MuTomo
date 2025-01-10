#include "action.hh"

MyactionInitialization::MyactionInitialization()
{}

MyactionInitialization::~MyactionInitialization()
{}

void MyactionInitialization::Build() const
{
	auto *generator = new MuonGenerator();
	SetUserAction(generator);
}