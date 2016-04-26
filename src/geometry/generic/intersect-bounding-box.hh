#pragma once

namespace eScatter { namespace geometry
{
    namespace generic
    {
        /*! Ray BoundingBox intersection.
         */
        template <typename K>
        bool intersect(
            typename K::BoundingBox const &bb,
            typename K::Ray const &ray,
            typename K::real_t &time_1,
            typename K::real_t &time_2)
        {
            using Vector = typename K::Vector;

            Vector t0 = (bb.min - ray.origin) / ray.direction,
                   t1 = (bb.max - ray.origin) / ray.direction;

            time_1 = max_element(Vector::min(t0, t1));
            time_2 = min_element(Vector::max(t0, t1));

            return time_2 >= time_1 && time_2 >= 0;
        }
    }
} } // eScatter::geometry

