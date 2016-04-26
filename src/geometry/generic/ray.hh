#pragma once

namespace eScatter { namespace geometry
{
    namespace generic
    {
        template <typename K>
        class Ray: public K
        {
            using typename K::Point;
            using typename K::Vector;
            using typename K::Direction;
            using typename K::real_t;

            public:
                Point origin;
                Direction direction;

                Ray(Point const &origin, Vector const &direction):
                    origin(origin), direction(direction) {}

                Ray(Point const &origin, Direction const &direction):
                    origin(origin), direction(direction) {}

                Point operator()(real_t time) const
                    { return origin + time * direction; }
        };
    }
}}

