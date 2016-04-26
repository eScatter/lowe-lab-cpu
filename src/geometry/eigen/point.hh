#pragma once
#include "vector.hh"

namespace eScatter { namespace geometry
{
    namespace eigen
    {
        template <typename K>
        class Point
        {
            friend class Vector<K>;
            using real_t = typename K::real_t;
            using vec_t = Eigen::Matrix<real_t, 3, 1>;
            using array_t = Eigen::Array<real_t, 3, 1>;

            vec_t data_;

            public:
                Point() {};
                // Point(std::array<real_t, 3> const &p):
                //    data_(p[0], p[1], p[2]) {}
                Point(real_t x, real_t y, real_t z):
                    data_(x, y, z) {}

                inline real_t const &x() const { return data_(0); }
                inline real_t const &y() const { return data_(1); }
                inline real_t const &z() const { return data_(2); }

                inline real_t &x() { return data_(0); }
                inline real_t &y() { return data_(1); }
                inline real_t &z() { return data_(2); }

                Vector<K> operator-(Point const &other) const
                    { return Vector<K>(data_ - other.data_); }
                Point operator+(Vector<K> const &other) const
                    { return Point(data_ + other.data_); }
                Point operator-(Vector<K> const &other) const
                    { return Point(data_ - other.data_); }

                Point &operator+=(Vector<K> const &other)
                    { return data_ += other.data_; }
                Point &operator-=(Vector<K> const &other)
                    { return data_ -= other.data_; }

                real_t const &operator[](size_t idx) const
                    { return data_(idx); }
                real_t &operator[](size_t idx)
                    { return data_(idx); }

                static Point origin()
                    { return Point(0, 0, 0); }

                static Point min(Point const &a, Point const &b)
                    { return Point(a.data_.array().min(b.data_.array())); }
                static Point max(Point const &a, Point const &b)
                    { return Point(a.data_.array().max(b.data_.array())); }

            private:
                Point(vec_t &&a):
                    data_(a) {}
        };
    } // namespace eigen
}} // namespace eScatter::geometry

