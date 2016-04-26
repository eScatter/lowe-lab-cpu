#pragma once
#include "vector.hh"
#include "../generic/ray.hh"
#include "../generic/triangle.hh"
#include "../generic/bounding-box.hh"
#include "../generic/intersect.hh"
#include "direction-type.hh"

namespace eScatter
{
    namespace geometry
    {
        template <typename T>
        class Slow
        {
            public:
                typedef T real_t;

                typedef slow::Point<Slow> Point;
                typedef slow::Vector<Slow> Vector;
                typedef slow::Direction<Slow> Direction;

                typedef generic::Ray<Slow> Ray;
                typedef generic::BoundingBox<Slow> BoundingBox;
                typedef generic::Triangle<Slow> Triangle;
        };
    }
}

