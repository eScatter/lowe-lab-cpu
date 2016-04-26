#pragma once

namespace eScatter { namespace geometry
{
    namespace generic
    {
        /*! Ray triangle intersection.
         *
         * Uses Möller & Trumbore. Journal of Graphics Tools, 1997.
         */
        template <typename K>
        bool intersect(
            typename K::Triangle const &triangle, 
            typename K::Ray const &ray,
            typename K::real_t &time,
            typename K::real_t epsilon)
        {
            using real_t = typename K::real_t;
            using Vector = typename K::Vector;

            Vector edge_1 = triangle[1] - triangle[0],
                   edge_2 = triangle[2] - triangle[0],
                   P = ray.direction % edge_2;

            real_t det = P(edge_1);

            // if determinant equals zero, the ray lies in the plane
            // of the triangle, we report no intersection.
            if (det > -epsilon && det < epsilon)
                return false;

            Vector T = ray.origin - triangle[0];
            real_t u = P(T) / det;

            // u should be in range [0, 1], or intersection is outside
            // triangle.
            if (u < 0. || u > 1.)
                return false;

            Vector Q = T % edge_1;
            real_t v = Q(ray.direction) / det;

            if (v < 0. || u + v > 1.)
                return false;

            real_t t = Q(edge_2) / det;

            if (t < epsilon)
                return false;
            
            time = t;
            return true;
        }
    }
} } // eScatter::geometry

