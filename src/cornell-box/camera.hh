#pragma once
#include "cornell.hh"
#include "material.hh"

namespace cornell
{
    class Camera: public Object
    {
        public:
            Sphere shape;

            Point origin, target;
            Vector shub, axis_z, axis_y, axis_x;
            real_t delta_ra, delta_dec, radius;

            Camera(Point const &origin, Point const &target, Vector const &shub, 
                   real_t delta_ra, real_t delta_dec, real_t radius):
                Object(material::sensor), shape(origin, radius),
                target(target), shub(shub), 
                axis_z((target - origin).normalise()),
                delta_ra(delta_ra), delta_dec(delta_dec)
            {
                // create ortho-normal basis in camera plane
                Vector b1 = (axis_z % shub).normalise(),
                       b2 = (axis_z % b1).normalise();

                // project shub to the camera plane
                axis_y = (b1(shub) * b1 + b2(shub) * b2).normalise();
                axis_x = axis_z % axis_y;
            }

            BoundingBox bounding_box() const { return shape.bounding_box(); }
            Point centroid() const { return shape.centroid(); }
            Vector normal(Point const &p) const { return shape.normal(p); }

            bool intersect(Ray const &ray, real_t &time, real_t epsilon) const
            { return intersect(shape, ray, time, epsilon); }

            void add(Photon const &gamma)
            {
            }
    };
}

