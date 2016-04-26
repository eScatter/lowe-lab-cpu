#pragma once
#include "../geometry/generic/base.hh"
#include <algorithm>
#include <vector>

namespace soneira_peebles
{
    using eScatter::geometry::Origin;

    template <typename K>
    class SP
    {
        using real_t = typename K::real_t;
        using Point = typename K::Point;
        using Vector = typename K::Vector;

    public:
        template <typename Rng>
        static Vector vector_in_sphere(Rng &rng)
        {
            real_t phi = rng() * 2 * M_PI;       // right ascension
            real_t theta = asin(rng() * 2 - 1);  // azimuth
            real_t r = pow(rng(), 1./3);

            return Vector(
                cos(phi) * cos(theta) * r,
                sin(phi) * cos(theta) * r,
                sin(theta) * r);
        }

        template <typename Rng>
        static std::vector<Point> n_points_in_sphere(Rng &rng, unsigned n)
        {
            std::vector<Point> result;
            std::generate_n(std::back_inserter(result), n, [&rng] () {
                return Point(Origin) + vector_in_sphere(rng); });
            return result;
        }

        template <typename Rng>
        static std::vector<Point> multiply_points(Rng &rng,
            std::vector<Point> const &parents, 
            unsigned m, real_t scale)
        {
            std::vector<Point> result;
            for (Point const &O : parents)
                std::generate_n(std::back_inserter(result), m, 
                    [&rng, &O, scale] () {
                        return O + vector_in_sphere(rng) * scale; 
                    });
            return result;
        }

        template <typename Rng>
        static std::vector<Point> make(Rng &rng, unsigned n, unsigned m, real_t x)
        {
            std::vector<Point> pts = { Point(Origin) };
            real_t scale = 1.0;

            for (unsigned i = 0; i < n; ++i)
            {
                pts = multiply_points(rng, pts, m, scale);
                scale *= x;
            }

            return pts;
        }
    };
}

