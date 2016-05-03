#pragma once
#include "interface.hh"

namespace cornell
{
    class SpecularInterface: public Interface
    {
        public:
            SpecularInterface():
                Interface(SPECULAR) {}

            void interact(Photon &gamma, Direction const &normal) const;
    };
}

