#pragma once
#include "base.hh"

namespace cornell
{
    enum material_t
    {
        DIFFUSE, SPECULAR, REFRACTION, EMISSION, SENSOR
    };

    class Interface
    {
        public:
            material_t const type;

            Interface(material_t type_):
                type(type_) {}

            virtual void interact(Photon &gamma, Direction const &normal) const = 0;
    };
}

