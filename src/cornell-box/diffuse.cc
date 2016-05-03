#include "diffuse.hh"
#include <random>

using namespace cornell;

template <typename R>
Direction random_direction(R &rng)
{
    auto unit = std::bind(std::uniform_real_distribution<real_t>(0.0, 1.0), rng);
    real_t phi = unit() * 2 * M_PI;       // right ascension
    real_t theta = asin(unit() * 2 - 1);  // azimuth

    return Direction(
        cos(phi) * cos(theta),
        sin(phi) * cos(theta),
        sin(theta));
}

void DiffuseInterface::interact(Photon &gamma, Direction const &normal) const
{
    auto &rng = gamma.rng();
    Direction a = random_direction(rng);
    real_t dp = normal(a);

    gamma.intensity *= normal(gamma.ray.direction) * albedo_(gamma.wavelength);
    gamma.ray.direction = (dp < 0.0 ? -a : a);
}

