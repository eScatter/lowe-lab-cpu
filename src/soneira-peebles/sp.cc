#include "../main/command.hh"
#include "../main/argparse.hh"
#include "../support/misc/iterators.hh"
#include "../numeric/ndarray.hh"
#include "../geometry/slow/kernel.hh"
#include "../geometry/generic/sphere.hh"
#include "../geometry/bvh/tree.hh"
#include "../geometry/bvh/object.hh"
#include "../numeric/hilbert.hh"

#include "../support/timer.hh"
#include "../support/png.hh"
#include "../support/misc/format.hh"

#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

#include "sp.hh"
#include "camera.hh"

namespace soneira_peebles
{
    using eScatter::geometry::bvh::ObjectAdaptor;
    using eScatter::geometry::generic::Sphere;

    template <typename K>
    using SphereObject = ObjectAdaptor<K, Sphere<K>>;

    template <typename Object>
    using BVH = eScatter::geometry::bvh::Tree<Object>;
}

using namespace soneira_peebles;
using namespace eScatter;
using namespace System;

using argparse::Option;
using K = geometry::Slow<double>;
using numeric::shape_t;
using eScatter::geometry::bvh::IntersectionInfo;
using eScatter::write_png;
using System::format;

Command cmd_sp("sp",
    "Test tree performance using Soneira-Peebles random fractal "
    "distribution of spheres.", 
    [] (std::vector<std::string> const &args_)
{
    using real_t = typename K::real_t;
    using Point = typename K::Point;
    using Vector = typename K::Vector;
    using Ray = typename K::Ray;

    argparse::Args args = {
        Option("-n", "depth of the fractal", "8"),
        Option("-m", "multiplicity", "3"),
        Option("-x", "scale", "0.5"),
        Option("-s", "size", "0.01"),
        Option("-seed", "random seed (defaults to seconds since epoch)", ""),
        Option("-o", "png output file name", "sp.png"),
        Option("-no-png", "suppress png output"),
        Option("-machine", "machine readable stats to stdout"),
        Option("-H", "use Hilbert curves"),
        Option("-R", "randomise sampling, achieving worst case")
    };

    args.parse(tail(args_));

    int n = *args.get<int>("-n"),
        m = *args.get<int>("-m");

    double x = *args.get<double>("-x"),
           s = *args.get<double>("-s");

    std::map<std::string, std::string> profile;

    // setup random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    seed = args.get_fallback<unsigned>("-seed", seed);
    auto rng = std::bind(std::uniform_real_distribution<real_t>(), std::mt19937(seed));

    // create spheres
    Timer time_generate("generating Soneira-Peebles fractal");
    std::vector<Point> point_set = SP<K>::make(rng, n, m, x);
    profile["n-particles"] = format(point_set.size());
    auto spheres = std::make_unique<std::vector<SphereObject<K>>>();
    std::transform(point_set.begin(), point_set.end(), std::back_inserter(*spheres),
        [s] (Point const &p) { return SphereObject<K>(p, s); });
    time_generate.report();
    
    // build BVH    
    Timer time_build("building bvh");
    BVH<SphereObject<K>> bvh(std::move(spheres));
    profile["build-time"] = format(time_build.elapsed());
    profile["n-nodes"] = format(bvh.number_of_nodes());
    profile["n-leaves"] = format(bvh.number_of_leaves());
    time_build.report();
    std::cerr << bvh.number_of_nodes() << " nodes, of which "
              << bvh.number_of_leaves() << " leaves.\n";

    shape_t<2> shape = {2048, 2048};
    Camera<K> cam(
        Point(2.0, 2.0, 2.0),            // origin
        Point(0.0, 0.0, 0.0),            // target
        Vector(0.0, 0.0, 1.0),           // points up
        M_PI / 4,                        // delta RA
        (M_PI / 4 * shape[1])/shape[0]); // delta Dec.

    std::vector<size_t> walk(2048*2048);
    std::iota(walk.begin(), walk.end(), 0);

    if (*args.get<bool>("-H"))
    {
        Timer time_hilbert("computing Hilbert shuffle");
        walk = eScatter::numeric::hilbert_walk(11);
        time_hilbert.report();
    }
    else if (*args.get<bool>("-R"))
    {
        Timer time_randomize("shuffling indices");
        auto rng = std::mt19937(seed);
        std::shuffle(walk.begin(), walk.end(), rng);
        time_randomize.report();
    }

    Timer time_render("rendering");
    auto image = cam.render([&bvh] (Ray const &photon) -> real_t { 
        IntersectionInfo<SphereObject<K>> info = { 1.0e6, nullptr };
        if (bvh.find_intersection(photon, info, false, 1e-12))
        {
            if (info.object == NULL) return -1.0;
            Vector normal = info.object->normal(photon(info.time));
            return -normal(photon.direction);
        }

        return 0.0;
    }, shape, walk);
    profile["render-time"] = format(time_render.elapsed());
    time_render.report();

    if (!*args.get<bool>("-no-png"))
    {
        std::string output_fn = *args.get<std::string>("-o");
        std::cerr << "writing output to '" << output_fn << "'.\n"; std::cerr.flush();
        write_png<real_t>(*image, output_fn);
    }

    if (*args.get<bool>("-machine"))
    {
        auto const &first = head(profile);
        std::cout << "{\"" << first.first << "\":" << first.second;
        for (auto const &rest : tail(profile))
            std::cout << ",\"" << rest.first << "\":" << rest.second;
        std::cout << "}\n";
    }

    return 0;
});

