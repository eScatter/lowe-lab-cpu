#pragma once
#include "interface.hh"
#include <functional>

namespace cornell
{
    class SensorInterface: public Interface
    {
        public:
            SensorInterface():
                Interface(SENSOR) {}

            void interact(Photon &gamma, Direction const &normal) const
            {}
    };
}

