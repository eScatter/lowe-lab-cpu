#pragma once
#include "vector.hh"

namespace eScatter { namespace geometry {
    namespace eigen
    {
        template <typename K>
        class Direction: public K::Vector
        {
            // template <typename L>
            // friend typename L::Vector operator/(
            //         typename L::Vector const &v,
            //         typename L::Direction const &d);

            using Vector = typename K::Vector;
            using real_t = typename K::real_t;


            public:
                Vector inverse;

                Direction(Vector const &v):
                    Vector(v), inverse(1.0 / v.data_.array()) {}
        };

        template <typename K>
        inline Vector<K> operator/(Vector<K> const &v, Direction<K> const &d)
        {
            return v * d.inverse;
        }
    } // namespace eigen
}} // namespace eScatter::geometry

