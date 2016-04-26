#pragma once
#include <array>
#include <cmath>


namespace eScatter { namespace geometry
{
    namespace slow
    {
        template <typename K>
        class Vector: public std::array<typename K::real_t,3>
        {
            using real_t = typename K::real_t;

            public:
                Vector() {};

                Vector(real_t x, real_t y, real_t z):
                    std::array<real_t,3>({x, y, z})
                {}

                inline real_t const &x() const { return this->at(0); }
                inline real_t const &y() const { return this->at(1); }
                inline real_t const &z() const { return this->at(2); }

                inline real_t &x() { return this->at(0); }
                inline real_t &y() { return this->at(1); }
                inline real_t &z() { return this->at(2); }

                real_t operator()(Vector const &o) const
                {
                    return x()*o.x() + y()*o.y() + z()*o.z();
                }

                real_t norm() const
                {
                    return sqrt((*this)(*this));
                }

                Vector normalise() const
                { 
                    return (*this) / norm();
                }

                /*! point-wise minimum of two vectors */
                static Vector min(Vector const &a, Vector const &b)
                {
                    return Vector(
                        std::min(a.x(), b.x()),
                        std::min(a.y(), b.y()),
                        std::min(a.z(), b.z()));
                }

                /*! point-wise maximum of two vectors */
                static Vector max(Vector const &a, Vector const &b)
                {
                    return Vector(
                        std::max(a.x(), b.x()),
                        std::max(a.y(), b.y()),
                        std::max(a.z(), b.z()));
                }
        };
    }
}}

