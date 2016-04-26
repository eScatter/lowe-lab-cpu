#pragma once

namespace eScatter { namespace geometry { namespace generic {
    template <typename K>
    class Sphere
    {
            using real_t = typename K::real_t;
            using Point = typename K::Point;
            using Vector = typename K::Vector;
            using Ray = typename K::Ray;
            // using Direction = typename K::Direction;
            using BoundingBox = typename K::BoundingBox;

        public:
            Point centre;
            real_t radius;

            Sphere(Point const &p, real_t r):
                centre(p), radius(r) {}

            BoundingBox bounding_box() const
            {
                Vector a(radius, radius, radius);
                return BoundingBox(centre - a, centre + a);
            }

            Point centroid() const
            {
                return centre;
            }

            Vector normal(Point const &p) const
            {
                return p - centre;
            };
            
   /*         bool intersect(Ray const &ray, real_t &time, real_t epsilon)
            {
                Vector v = centre - ray.origin;
                Direction p = ray.direction;

                real_t a = p(p), b = -2.0 * v(p), c = v(v) - radius*radius;
                real_t d = b * b - 4 * a * c;
                if (d < epsilon) return false;

                time = (-b - sqrt(d)) / (2.0 * a);
                if (time < epsilon)
                    time = (-b + sqrt(d)) / (2.0 * a);
                return true;
            } */
    };
}}} // namespace eScatter::geometry::generic

