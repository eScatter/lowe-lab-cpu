#pragma once

namespace eScatter { namespace geometry
{
    namespace generic
    {
        template <typename K>
        class Triangle: public K, public std::array<typename K::Point, 3>
        {
            using typename K::Point;
            using typename K::Vector;
            using typename K::BoundingBox;
            
            using Base = std::array<Point, 3>;
            using Base::at;

            public:
                Triangle() = default;

                Triangle(Point const &a, Point const &b, Point const &c):
                    Base({a, b, c}), 
                    normal_(normalise((b - a) % (c - a))) {}

                Triangle(Point const &a, Point const &b, Point const &c, 
                         Vector const &n):
                    Base({a, b, c}), 
                    normal_(n) {}

                BoundingBox bounding_box() const
                {
                    return BoundingBox(*this);
                }

                Point centroid() const
                {
                    return at(0) + ((at(1) - at(0)) + (at(2) - at(0))) / 3.0;
                }

                Vector const &normal() const
                {
                    return normal_; 
                }

            private:
                Vector normal_;
        };
    } // namespace geometry
}} // namespace eScatter

