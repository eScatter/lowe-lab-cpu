#pragma once
#include "../numeric/tabulated.hh"
#include "../support/constants.hh"
#include <functional>
#include <algorithm>
#include <cmath>
#include <random>
#include <utility>


namespace cornell
{
    using namespace eScatter;
    using numeric::Tabulated;

    /*! Unitless normalised Planck radiation function. */
    template <typename real_t>
    inline real_t planck_function(real_t x)
    {
        constexpr real_t A = 15. / (M_PI * M_PI * M_PI * M_PI);
        return A / (pow(x, 5) * (exp(1. / x) - 1));
    }

    /*! Black body PDF. */
    template <typename real_t>
    std::function<real_t (real_t)> black_body_pdf(real_t T)
    {
        using namespace constants;
        const real_t A = k * T / (h * c) * 1e-6;    // (μm)⁻¹

        return [A] (real_t l)
        {
            return planck_function<real_t>(A * l);
        };
    }

    /*! Creates inverse of the cumulative distribution function for photons leaving
     * a black body radiator. The distribution is limited to visible light, having
     * a wavelength between 0.38 and 0.78 microns.
     *
     * \param temperature The temperature of the black-body in degrees Kelvin.
     * \return the CDF by tabulating numerically integrated values.
     */
    template <typename real_t>
    inline Tabulated<real_t> black_body_icdf(real_t temperature)
    {
        return Tabulated<real_t>::inverse_cdf(
                black_body_pdf<real_t>(temperature), 
                0.390, 0.830, 256, 1e-6);
    }

    template <typename real_t>
    class BlackBody
    {
        std::function<real_t ()> uniform;
        Tabulated<real_t> icdf;

        public:
            template <typename Rng>
            BlackBody(Rng &rng, real_t temperature):
                uniform(std::bind(std::uniform_real_distribution<real_t>(0.0, 1.0), rng)),
                icdf(black_body_icdf<real_t>(temperature))
            {}

            real_t operator()()
            {
                return icdf(uniform());
            }
    };
}

