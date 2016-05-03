#pragma once
#include "interface.hh"
#include <functional>

namespace cornell
{
    class EmissionInterface: public Interface
    {
        std::function<real_t (real_t)> spectrum;

        public:
            EmissionInterface(std::function<real_t (real_t)> spectrum):
                Interface(EMISSION), spectrum(spectrum) {}

            void interact(Photon &gamma, Direction const &normal) const;
    };
}

