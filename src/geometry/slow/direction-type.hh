#pragma once
#include <limits>
#include "vector-type.hh"

namespace eScatter { namespace geometry { namespace slow
{
    template <typename K>
    class Direction: public K::Vector
    {
        using Vector = typename K::Vector;
        using real_t = typename K::real_t;

        /* I can't seem to get the operator/ as a friend */

        public:
            Vector inverse;

            Direction(Vector const &v):
                Vector(v)
            {
                real_t const inf = std::numeric_limits<real_t>::infinity();
                for (unsigned i = 0; i < 3; ++i)
                    inverse[i] = (v[i] == 0.0 ? inf : 1.0 / v[i]);
            }
    };
    
    template <typename K>
    inline Vector<K> operator/(Vector<K> const &v, Direction<K> const &d)
    {
        return v * d.inverse;
    }
}}} // namespace eScatter::geometry::slow

