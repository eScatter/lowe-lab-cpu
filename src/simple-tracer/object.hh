#pragma once
#include "../geometry/generic/base.hh"
#include "../geometry/generic/triangle.hh"
#include "../geometry/generic/intersect.hh"

namespace eScatter { namespace simple 
{ 
    enum Material {
        DIFFUSE,
        DETECTOR,
        ESCAPE
    };

    namespace object 
    {
        template <typename K>
        class Object: public K
        {
            public:
                using typename K::Point;
                using typename K::Vector;
                using typename K::BoundingBox;
                using typename K::Ray;
                using typename K::real_t;

                virtual BoundingBox bounding_box() const = 0;
                virtual Point centroid() const = 0;
                virtual bool intersect(Ray const &ray, real_t &time, real_t epsilon) const = 0;
                virtual Vector normal(Ray const &ray, real_t const &time) const = 0;
                virtual Material const &material() const = 0;
        };

        template <typename K, typename T>
        class ObjectAdaptor: public Object<K>, public T
        {
            public:
                using BoundingBox = typename K::BoundingBox;
                using Point = typename K::Point;
                using Ray = typename K::Ray;
                using Vector = typename K::Vector;
                using real_t = typename K::real_t;

                using T::T;

                virtual BoundingBox bounding_box() const
                    { return T::bounding_box(); }
                virtual Point centroid() const
                    { return T::centroid(); }
                virtual bool intersect(Ray const &ray, real_t &time, real_t epsilon) const
                    { return geometry::generic::intersect<K>(*this, ray, time, epsilon); }
                virtual Vector normal(Ray const &ray, real_t const &time) const
                    { return T::normal(ray, time); }
                virtual Material const &material() const
                    { return T::material(); }
        };

        template <typename K>
        class Triangle: public geometry::generic::Triangle<K>
        {
            using Base = geometry::generic::Triangle<K>;
            Material material_;

            public:
                using Vector = typename K::Vector;
                using Point = typename K::Point;
                using Ray = typename K::Ray;
                using real_t = typename K::real_t;
                using BoundingBox = typename K::BoundingBox;

                Triangle() {}

                Triangle(Point const &a, Point const &b, Point const &c,
                         Material m):
                    Base(a, b, c), material_(m) {}

                Material const &material() const
                {
                    return material_;
                }

                Vector normal(Ray const &ray, real_t const &time) const
                { 
                    return Base::normal();
                }
        };

        template <typename K>
        using TriangleObject = ObjectAdaptor<K, Triangle<K>>;
}}} // namespace eScatter::simple

