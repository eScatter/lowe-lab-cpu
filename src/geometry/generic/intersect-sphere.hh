#pragma once
#include "sphere.hh"

namespace eScatter { namespace geometry { namespace generic
{
    template <typename K>
    bool intersect(
        Sphere<K> const &sphere, 
        typename K::Ray const &ray,
        typename K::real_t &time,
        typename K::real_t epsilon)
    {
        using real_t = typename K::real_t;
        using Vector = typename K::Vector;
        using Direction = typename K::Direction;

        Vector v = sphere.centre - ray.origin;
        Direction p = ray.direction;
        real_t r = sphere.radius;

        real_t a = p(p), b = -2.0 * v(p), c = v(v) - r*r;
        real_t d = b * b - 4 * a * c;
        if (d < epsilon) return false;

        time = (-b - sqrt(d)) / (2.0 * a);
        if (time < epsilon)
            time = (-b + sqrt(d)) / (2.0 * a);
        return true;
    }
}}}

