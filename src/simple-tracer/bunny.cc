#include "base.hh"

#include "../main/command.hh"
#include "../support/ply/ply.hh"
#include "../support/misc/iterators.hh"
#include "../support/timer.hh"
#include "../support/png.hh"
#include "../geometry/bvh/tree.hh"
#include "../numeric/ndarray.hh"
#include "../numeric/hilbert.hh"

#include <algorithm>
#include <numeric>
#include <experimental/tuple>
#include <chrono>

namespace eScatter
{
    namespace simple
    {
        template <typename Range>
        void scale_to_unit_cube(Range &pts)
        {
            auto bb = BoundingBox(pts);
            Vector extent = bb.extent();
            real_t max_extent = max_element(extent);

            Vector unit_extent = extent / max_extent;
            Point unit_origin = Point::origin() + (Vector(1,1,1) - unit_extent) / 2.0;

            for (auto &p : pts)
                p = unit_origin + (p - bb.min) / max_extent;
        }
    }
}

using namespace eScatter::simple;
using System::transmogrify;
using System::Timer;
using eScatter::write_png;

Command cmd_bunny("bunny",
    "Test simple bvh-based ray-tracer.",
    [] (std::vector<std::string> const &args)
{
    if (args.size() < 3)
    {
        std::cerr << "Give the filename of the PLY file as an argument.\n";
        return 1;
    }

    PLY::PLY bunny(args[2]);

    // read vertices
    std::vector<Point> pts(bunny["vertex"].size());
    transmogrify(bunny["vertex"].as_array<double, 3>(), pts.begin(),
        [] (double x, double y, double z)
        { return Point(x, y, z); });

    scale_to_unit_cube(pts);

    // read triangles
    auto tri = std::make_unique<std::vector<Object>>(bunny["face"].size());
    transmogrify(bunny["face"].as<std::vector<unsigned>>(), tri->begin(),
        [&pts] (std::vector<unsigned> const &f)
    {
        return Object(pts[f[0]], pts[f[1]], pts[f[2]], DIFFUSE);
    });
    std::cerr << "loaded " << args[2] << ": " << tri->size() << " triangles.\n";

    Timer time_build("building bvh");
    BVH bvh(std::move(tri));
    time_build.report();
    std::cerr << bvh.number_of_nodes() << " nodes, of which "
              << bvh.number_of_leaves() << " leaves.\n";

    shape_t<2> shape = {4096, 4096};
    Camera cam(
        Point(2.0, 2.0, 2.0),            // origin
        Point(0.5, 0.5, 0.5),            // target
        Vector(0.0, 0.0, 1.0),           // points up
        M_PI / 8,                        // delta RA
        (M_PI / 8 * shape[1])/shape[0]); // delta Dec.

    Timer time_hilbert("computing Hilbert shuffle");
    auto hilbert = eScatter::numeric::hilbert_walk(12);
    time_hilbert.report();

    Timer time_render("rendering");
    auto image = cam.render([&bvh] (Ray const &photon) -> real_t { 
        IntersectionInfo info = { 1.0e6, nullptr };
        if (bvh.find_intersection(photon, info, false, 1e-12))
        {
            if (info.object == NULL) return -1.0;
            Vector normal = info.object->normal(photon, info.time);
            return -normal(photon.direction);
        }

        return 0.0;
    }, shape, hilbert);
    time_render.report();

    std::cerr << "writing output to 'test.png'.\n"; std::cerr.flush();

    write_png<real_t>(*image, "test.png");

    return 0;
});

