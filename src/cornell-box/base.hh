#pragma once
#include "../geometry/slow/kernel.hh"
#include "../geometry/generic/sphere.hh"

#include "rng.hh"

namespace cornell
{
    using namespace eScatter;
    using K = geometry::Slow<float>;

    using real_t = K::real_t;
    using Point = K::Point;
    using Vector = K::Vector;
    using Direction = K::Direction;
    using Ray = K::Ray;
    using Sphere = geometry::Sphere<K>;

    class Photon
    {
        public:
            Ray ray;
            real_t wavelength;   // μm
            real_t intensity;    // W/m²

            std::mt19937 &rng()
            {
                return Rng::generator();
            }
    };
}

