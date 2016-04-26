#pragma once
#include "vector.hh"
#include "triangle.hh"
#include "bounding_box.hh"

namespace eScatter
{
    namespace geometry
    {
        class Scene
        {
            public:
                class Face: public std::array<size_t, 3>
                {
                    Solid const *solid_;
                    Face const *opposite_;
                    Vector normal_;


                };

                Triangle triangle(Face const &f) const
                {
                    return Triangle(vertices_[f[0]], vertices_[f[1]], vertices_[f[2]]);
                }

                BoundingBox bounding_box() const
                {
                    return BoundingBox(vertices_);
                }

            private:
                std::vector<Point> vertices_;
                std::vector<Face> faces_;
                std::vector<Solid> solids_;
        };
    } // namespace geometry
} // namespace eScatter
