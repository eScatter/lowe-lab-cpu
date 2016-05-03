#include "specular.hh"

using namespace cornell;

void SpecularInterface::interact(Photon &gamma, Direction const &normal) const
{
    gamma.ray.direction = normal.mirror(gamma.ray.direction);
}

