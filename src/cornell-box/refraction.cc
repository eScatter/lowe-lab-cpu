#include "refraction.hh"
#include <random>
#include <cmath>

using namespace cornell;

real_t SellmeierEquation::operator()(real_t l) const
{
    real_t m = l * l;
    return sqrt(1 + B1 * m / (m - C1)
            + B2 * m / (m - C2)
            + B3 * m / (m - C3));
}

real_t cornell::unpolarised_reflectance(real_t n1, real_t n2, real_t mu_i, real_t mu_t)
{
    real_t R_s = pow((n1 * mu_i - n2 * mu_t) / (n1 * mu_i + n2 * mu_t), 2.0),
           R_p = pow((n1 * mu_t - n2 * mu_i) / (n1 * mu_t + n2 * mu_i), 2.0);
    return (R_s + R_p) / 2.0;
}

void RefractionInterface::interact(Photon &gamma, Direction const &normal) const
{
    auto unit = std::bind(std::uniform_real_distribution<real_t>(0.0, 1.0), gamma.rng());

    real_t dp = normal(gamma.ray.direction),
           n1 = 1.0, n2 = refraction_index(gamma.wavelength);

    if (dp > 0.0)
        std::swap(n1, n2);

    real_t mu_t = sqrt(1 - pow(n1 / n2, 2) * (1 - dp*dp));
    real_t R = unpolarised_reflectance(n1, n2, abs(dp), mu_t);

    if (unit() > R)
        // refraction
        gamma.ray.direction = dp * normal + (n1 / n2) * (dp * normal - gamma.ray.direction);
    else 
        // reflection
        gamma.ray.direction = normal.mirror(gamma.ray.direction);
}

