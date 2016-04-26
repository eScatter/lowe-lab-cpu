#pragma once
#include "vector.hh"
#include "point.hh"
#include "direction.hh"

#include "../generic/ray.hh"
#include "../generic/triangle.hh"
#include "../generic/bounding-box.hh"

namespace eScatter { namespace geometry
{
    /*! The Eigen based vector kernel. Eigen is highly optimised, using
     * both expression templates and SSE accelerated vector operations.
     * Using this kernel should give a significant speed-up with respect
     * to the std::array based vector kernel.
     */
    template <typename T>
    class Eigen
    {
        public:
            typedef T real_t;

            typedef eigen::Vector<Eigen<T>> Vector;
            typedef eigen::Point<Eigen<T>> Point;
            typedef eigen::Direction<Eigen<T>> Direction;

            typedef generic::Ray<Eigen<T>> Ray;
            typedef generic::Triangle<Eigen<T>> Triangle;
            typedef generic::BoundingBox<Eigen<T>> BoundingBox;
    };

    inline std::ostream &operator<<(std::ostream &out, typename Eigen<float>::Point const &p)
    {
        return out << p.x() << " " << p.y() << " " << p.z();
    }
} } // namespace eScatter::geometry

