#include "interface.hh"
#include <functional>

namespace cornell
{
    class DiffuseInterface: public Interface
    {
        std::function<real_t (real_t)> albedo_;

        public:
            DiffuseInterface(std::function<real_t (real_t)> const &albedo_):
                Interface(DIFFUSE), albedo_(albedo_) {}

            void interact(Photon &gamma, Direction const &normal) const;
    };
}

