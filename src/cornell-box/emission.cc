#include "emission.hh"

using namespace cornell;

void EmissionInterface::interact(Photon &gamma, Direction const &normal) const
{
    gamma.intensity = 0.0; // absorb the photon
}

