#pragma once
#include "../generic/base.hh"
#include <Eigen/Dense>

namespace eScatter { namespace geometry
{
    namespace eigen
    {
        template <typename K> class Point;
        template <typename K> class Direction;

        template <typename K>
        class Vector
        {
            friend class Point<K>;
            friend class Direction<K>;

            using real_t = typename K::real_t;
            using vec_t = Eigen::Matrix<real_t, 3, 1>;
            using array_t = Eigen::Array<real_t, 3, 1>;

            vec_t data_;

            public:
                Vector() {};

                Vector(real_t x, real_t y, real_t z):
                    data_(x, y, z) {}

                inline real_t const &x() const { return data_(0); }
                inline real_t const &y() const { return data_(1); }
                inline real_t const &z() const { return data_(2); }

                inline real_t &x() { return data_(0); }
                inline real_t &y() { return data_(1); }
                inline real_t &z() { return data_(2); }

                Vector &operator+=(Vector const &other)
                    { data_ += other.data_; return *this; }
                Vector &operator-=(Vector const &other)
                    { data_ -= other.data_; return *this; }
                Vector &operator*=(real_t scale)
                    { data_ *= scale; return *this; }
                Vector &operator/=(real_t scale)
                    { data_ /= scale; return *this; }

                Vector operator+(Vector const &other) const
                    { return Vector(data_ + other.data_); }
                Vector operator-(Vector const &other) const
                    { return Vector(data_ - other.data_); }
                Vector operator*(real_t scale) const
                    { return Vector(data_ * scale); }
                Vector operator/(real_t scale) const
                    { return Vector(data_ / scale); }
                Vector operator*(Vector const &other) const
                    { return Vector(data_.array() * other.data_.array()); }
                Vector operator%(Vector const &other) const
                    { return Vector(data_.cross(other.data_)); }
                real_t operator()(Vector const &other) const
                    { return data_.dot(other.data_); }

                real_t const &operator[](size_t idx) const
                    { return data_(idx); }
                real_t &operator[](size_t idx)
                    { return data_(idx); }

                real_t norm() const
                    { return data_.norm(); }

                Vector normalise() const
                    { return (*this) / norm(); }

                static Vector min(Vector const &a, Vector const &b)
                    { return Vector(a.data_.array().min(b.data_.array())); }
                static Vector max(Vector const &a, Vector const &b)
                    { return Vector(a.data_.array().max(b.data_.array())); }

                inline real_t max_element() const { return data_.maxCoeff(); }
                inline real_t min_element() const { return data_.minCoeff(); }

            private:
                Vector(vec_t &&a):
                    data_(a) {}
        };

        template <typename K>
        Vector<K> operator*(typename K::real_t scale, Vector<K> const &a)
            { return a * scale; }

        template <typename K>
        Vector<K> normalise(Vector<K> const &a)
            { return a / a.norm(); }

        template <typename K>
        inline typename K::real_t max_element(Vector<K> const &v)
        {
            return v.max_element();
            //return std::max(v[0], std::max(v[1], v[2]));
        }

        template <typename K>
        inline typename K::real_t min_element(Vector<K> const &v)
        {
            return v.min_element();
            //return std::min(v[0], std::min(v[1], v[2]));
        }

    }
} } // namespace eScatter::geometry


