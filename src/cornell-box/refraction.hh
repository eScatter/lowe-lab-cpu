#pragma once
#include "interface.hh"
#include <functional>

namespace cornell
{
    /*! \brief Fresnel reflectance for unpolarised light.
     *
     * We compute both the reflectance for s-polarised light as
     *  \f[
     *      R_s = \left(\frac{n_1 \cos \theta_i - n_2 \cos \theta_t}
     *          {n_1 \cos \theta_i + n_2 \cos \theta_t}\right)^2,
     *  \f] 
     * and the reflectance for p-polarised light as
     *  \f[
     *      R_p = \left(\frac{n_1 \cos \theta_t - n_2 \cos \theta_i}
     *          {n_1 \cos \theta_t + n_2 \cos \theta_i}\right)^2,
     *  \f] 
     * and take the average
     *  \f[
     *      R = \frac{R_s + R_p}{2}.
     *  \f]
     *
     * \param n1 The refractive index of the first medium.
     * \param n2 The refractive index of the second medium.
     * \param mu_i \f$\cos \theta_i\f$, the cosine of the angle of incidence.
     * \param mu_t \f$\cos \theta_t\f$, the cosine of the angle of transmission.
     * \return The probability that a ray reflects.
     */
    extern real_t unpolarised_reflectance(real_t n1, real_t n2, real_t mu_i, real_t mu_t);


    /*! \brief The Sellmeier equation is a fitting formula for the
     * wavelength dependence of the refractive index.
     *
     * The formula takes six parameters:
     * \f[
     *      n^2 = 1 + \frac{B_1 \lambda^2}{\lambda^2 - C_1}
     *          + \frac{B_2 \lambda^2}{\lambda^2 - C_2}
     *          + \frac{B_3 \lambda^2}{\lambda^2 - C_3}
     * \f]
     * 
     * The parameters for the Sellmeier equation for a number of substances 
     * can be found on [RefractiveIndex.info](http://refractiveindex.info/).
     */
    class SellmeierEquation
    {
        public:
            real_t B1, C1, B2, C2, B3, C3;

            real_t operator()(real_t l) const;
    };


    /*! \brief Interaction of a photon with a refractive surface.
     *
     * Uses the wavelength dependent refraction index of the material to compute
     * the refraction angle and the probability that the photon will reflect,
     * then based on this reflectance choose to reflect or refract.
     */
    class RefractionInterface: public Interface
    {
        std::function<real_t (real_t)> refraction_index;

        public:
            RefractionInterface(std::function<real_t (real_t)> n):
                Interface(REFRACTION), refraction_index(n) {}

            void interact(Photon &gamma, Direction const &normal) const;
    };
}

