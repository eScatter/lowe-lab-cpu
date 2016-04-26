#pragma once
#include "../numeric/ndarray.hh"

namespace soneira_peebles {
    using eScatter::numeric::NdArray;
    using eScatter::numeric::NdRange;
    using eScatter::numeric::shape_t;

    template <typename K>
    class Camera
    {
        using real_t = typename K::real_t;
        using Point = typename K::Point;
        using Vector = typename K::Vector;
        using Ray = typename K::Ray;

        public:
            Point origin, target;
            Vector shub, axis_z, axis_y, axis_x;
            real_t delta_ra, delta_dec;

            Camera(Point const &origin, Point const &target, Vector const &shub, 
                   real_t delta_ra, real_t delta_dec):
                origin(origin), target(target), shub(shub), 
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

            template <typename Fn>
            std::unique_ptr<NdArray<real_t, 2>> render(
                Fn fn, shape_t<2> const &shape, std::vector<size_t> const &shuffle)
            {
                auto result = std::make_unique<NdArray<real_t, 2>>(shape);
                auto slice = result->slice();

                Vector top_left = 1.0 * axis_z 
                    - sin(delta_ra/2) * axis_x
                    + sin(delta_dec/2) * axis_y;

                real_t res_x = delta_ra / shape[0],
                       res_y = delta_dec / shape[1];

                #pragma omp parallel for
                for (size_t i_ = 0; i_ < slice.size; ++i_)
                {
                    size_t i = shuffle[i_];
                    size_t stride = slice.shape[0];

                    Ray photon(origin, top_left 
                        + res_x * (i % stride) * axis_x
                        - res_y * (i / stride) * axis_y);

                    (*result)[i] = fn(photon);
                }

                return std::move(result);
            }
    };
}

