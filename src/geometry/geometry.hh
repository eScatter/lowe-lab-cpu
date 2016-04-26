#pragma once
#include "vector.hh"

namespace eScatter
{
    /*! Definitions and algorithms pertaining the application of geometry.
     *
     * The geometric computations are templated so that we achieve maximum
     * modularity on this level. This design pattern is loosely inspired on
     * that of CGAL, the Computational Geometry Algorithm Library.
     *
     * The idea is that, given a geometry 'kernel' or traits class, we obtain
     * the basic geometric definitions on which we can base a set of generic
     * algorithms. The traits class defines some concepts that are central to
     * doing ray-tracer geometry: points, vectors, rays, triangles, etc.
     * We keep with the CGAL tradition that points and vectors are different
     * things, in the sense that vectors have a measure, arithmetic and inner
     * product, whereas points strictly cary meaning, only when related to
     * other points.
     */
    namespace geometry
    {
    } // namespace geometry
} // namespace eScatter

