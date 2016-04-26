#pragma once
#include "../geometry/eigen/kernel.hh"
#include "../geometry/slow/kernel.hh"
#include "../geometry/bvh/tree.hh"
#include "../numeric/ndarray.hh"

#include "object.hh"
#include "camera.hh"

namespace eScatter
{
    namespace simple
    {
        using K = geometry::Slow<float>;

        using real_t = K::real_t;
        using Vector = K::Vector;
        using Point = K::Point;
        using Ray = K::Ray;
        using BoundingBox = K::BoundingBox;

        using Object = object::TriangleObject<K>;
        using BVH = geometry::bvh::Tree<Object>;
        using IntersectionInfo = geometry::bvh::IntersectionInfo<Object>;
        using Triangle = object::TriangleObject<K>;
        using Camera = camera::Camera<K>;

        using numeric::shape_t;
        using numeric::stride_t;
        using numeric::NdArray;
        using numeric::Slice;
        using numeric::NdRange;
    }
   
    // speed up compile times
    namespace geometry { namespace bvh {    
        extern template class geometry::bvh::Tree<simple::Object>;
    }}
}

