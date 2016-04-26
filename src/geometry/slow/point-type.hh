#pragma once
#include <array>
#include "vector-type.hh"
#include "../generic/base.hh"
#include <iostream>

namespace eScatter { namespace geometry
{
    namespace slow
    {

        template <typename K>
        class Point: public std::array<typename K::real_t,3>
        {
            using real_t = typename K::real_t;

            public:
                Point() {};

                Point(origin_t):
                    std::array<real_t,3>({0, 0, 0})
                {}

                Point(real_t x, real_t y, real_t z):
                    std::array<real_t,3>({x, y, z})
                {}

                inline real_t const &x() const { return this->at(0); }
                inline real_t const &y() const { return this->at(1); }
                inline real_t const &z() const { return this->at(2); }

                inline real_t &x() { return this->at(0); }
                inline real_t &y() { return this->at(1); }
                inline real_t &z() { return this->at(2); }

                static Point origin()
                    { return Point(0, 0, 0); }

                /*! point-wise minimum of two points */
                static Point min(Point const &a, Point const &b)
                {
                    return Point(
                        std::min(a.x(), b.x()),
                        std::min(a.y(), b.y()),
                        std::min(a.z(), b.z()));
                }

                /*! point-wise maximum of two points */
                static Point max(Point const &a, Point const &b)
                {
                    return Point(
                        std::max(a.x(), b.x()),
                        std::max(a.y(), b.y()),
                        std::max(a.z(), b.z()));
                }
        };

        template <typename K>
        std::ostream &operator<<(std::ostream &out, Point<K> const &p)
        {
            return out << p[0] << " " << p[1] << " " << p[2];
        }
    }
}}

