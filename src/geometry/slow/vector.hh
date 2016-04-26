#pragma once
#include "vector-type.hh"
#include "point-type.hh"
#include "vector-operators.hh"

namespace eScatter { namespace geometry
{
    namespace slow
    {
        template <typename K>
        inline typename K::real_t max_element(Vector<K> const &v)
        {
            return std::max(v[0], std::max(v[1], v[2]));
        }

        template <typename K>
        inline typename K::real_t min_element(Vector<K> const &v)
        {
            return std::min(v[0], std::min(v[1], v[2]));
        }

        template <typename K>
        inline Vector<K> normalise(Vector<K> const &a)
        {
            return a / a.norm();
        }
    } // namespace geometry
}} // namespace eScatter

