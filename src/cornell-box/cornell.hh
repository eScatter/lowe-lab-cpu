#pragma once
#include "base.hh"
#include "interface.hh"

#include "../geometry/bvh/tree.hh"
#include "../geometry/bvh/object.hh"

namespace cornell
{
    class Object: public geometry::bvh::Object<K>
    {
        Interface const &interface_;

        public:
            using BoundingBox = typename K::BoundingBox;
            using Vector = typename K::Vector;
            using Point = typename K::Point;
            using Ray = typename K::Ray;
            using real_t = typename K::real_t;

            Object(Interface const &interface_):
                interface_(interface_) {}

            Interface const &interface() const { return interface_; }
    };

    template <typename T>
    class ObjectAdaptor: public Object, public T
    {
        public:
            ObjectAdaptor(T const &solid_, Interface const &interface_):
                Object(interface_), T(solid_) {}

            virtual BoundingBox bounding_box() const
                { return T::bounding_box(); }
            virtual Point centroid() const
                { return T::centroid(); }
            virtual bool intersect(Ray const &ray, real_t &time, real_t epsilon) const
                { return geometry::generic::intersect<K>(*this, ray, time, epsilon); }
    };

    using Sphere = ObjectAdaptor<geometry::generic::Sphere<K>>;
    using Triangle = ObjectAdaptor<geometry::generic::Triangle<K>>;

    using ObjectPtr = geometry::bvh::ObjectPtr<K, std::unique_ptr<Object>>;
    using BVH = geometry::bvh::Tree<ObjectPtr>;
}

