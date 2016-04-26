#pragma once
#include "../generic/base.hh"
#include "../generic/triangle.hh"
#include "../generic/intersect.hh"

namespace eScatter { namespace geometry
{
    namespace bvh
    {
        using generic::Triangle;

        /*! BVH Object example.
         *
         * The Object base class that is used in the BVH algorithm, needs to
         * have three functions: bounding_box(), centroid(), and intersect().
         * One sure way to achieve this is to derive your Object base class
         * from this one.
         */
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
        };

        /*! BVH ObjectAdaptor, takes an object with the necessary functions
         * already implemented and have them derive from the virtual functions
         * provided in the Object<K> base class. This allows us to mix template
         * classes with dynamic abstraction.
         *
         * The intersect method calls the overloaded generic::intersect
         * function in stead of a class method.
         */
        template <typename K, typename T>
        class ObjectAdaptor: public Object<K>, public T
        {
            public:
                using BoundingBox = typename K::BoundingBox;
                using Vector = typename K::Vector;
                using Point = typename K::Point;
                using Ray = typename K::Ray;
                using real_t = typename K::real_t;

                using T::T;

                virtual BoundingBox bounding_box() const
                    { return T::bounding_box(); }
                virtual Point centroid() const
                    { return T::centroid(); }
                virtual bool intersect(Ray const &ray, real_t &time, real_t epsilon) const
                    { return generic::intersect<K>(*this, ray, time, epsilon); }
        };

        template <typename K>
        using TriangleObject = ObjectAdaptor<K, Triangle<K>>;
    } // namespace bvh
} } // namespace eScatter::geometry

