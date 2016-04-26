#include "../main/command.hh"
// #include "../geometry/slow/kernel.hh"
#include "../geometry/eigen/kernel.hh"
#include "../geometry/bvh/object.hh"
#include <iostream>

using namespace eScatter;
using namespace geometry;

using K = geometry::Eigen<float>;

Command cmd_intersect("intersect",
    "Try some intersections.",
    [] (std::vector<std::string> const &args)
{
    std::vector<K::Point> pts = {
        { 0.0, 0.0, 0.0 },
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 1.0, 1.0, 0.0 } };

    bvh::TriangleObject<K>
        t1(pts[0], pts[1], pts[2]),
        t2(pts[1], pts[3], pts[2]);

    K::Ray r1({0.0, 0.0, 1.0}, {1.0, 1.0, -5.0}),
           r2({1.0, 1.0, -1.0}, {-1.0, -0.5, 4.0});

    std::cout << "T1: " << t1[0] << " ; " << t1[1] << " ; " << t1[2] << std::endl;
    std::cout << "T2: " << t2[0] << " ; " << t2[1] << " ; " << t2[2] << std::endl;

    float t;
    double eps = 1e-6;
    if (t1.intersect(r1, t, eps))
        std::cout << "Triangle 1 intersects at " 
                  << r1.origin + t*r1.direction << std::endl;
    if (t2.intersect(r2, t, eps))
        std::cout << "Triangle 2 intersects at " 
                  << r2.origin + t*r2.direction << std::endl;

    return 0;
});

