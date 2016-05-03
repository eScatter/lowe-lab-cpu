#pragma once
#include "point-type.hh"
#include "vector-type.hh"

namespace eScatter { namespace geometry 
{
    namespace slow
    {
        /*-----------------------------------------------------------------
         * Point-Vector operators
         */

        template <typename K>
        Vector<K> operator-(Point<K> const &a, Point<K> const &b)
        {
            return Vector<K>(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
        }

        template <typename K>
        Point<K> operator+(Point<K> const &a, Vector<K> const &b)
        {
            return Point<K>(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
        }

        template <typename K>
        Point<K> operator-(Point<K> const &a, Vector<K> const &b)
        {
            return Point<K>(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
        }

        template <typename K>
        Point<K> &operator+=(Point<K> &a, Vector<K> const &b)
        {
            a.x() += b.x(); a.y() += b.y(); a.z() += b.z();
            return a;
        }

        template <typename K>
            Point<K> &operator-=(Point<K> &a, Vector<K> const &b)
        {
            a.x() -= b.x(); a.y() -= b.y(); a.z() -= b.z();
            return a;
        }

        /*-----------------------------------------------------------------
         * Vector-Vector operators
         */
        template <typename K>
        Vector<K> &operator+=(Vector<K> &a, Vector<K> const &b)
        {
            a.x() += b.x(); a.y() += b.y(); a.z() += b.z();
            return a;
        }

        template <typename K>
        Vector<K> &operator-=(Vector<K> &a, Vector<K> const &b)
        {
            a.x() -= b.x(); a.y() -= b.y(); a.z() -= b.z();
            return a;
        }

        template <typename K>
        Vector<K> &operator*=(Vector<K> &a, typename K::real_t scale)
        {
            a.x() *= scale; a.y() *= scale; a.z() *= scale;
            return a;
        }

        template <typename K>
        Vector<K> &operator/=(Vector<K> &a, typename K::real_t scale)
        {
            a.x() /= scale; a.y() /= scale; a.z() /= scale;
            return a;
        }

        template <typename K>
        Vector<K> operator+(Vector<K> const &a, Vector<K> const &b)
        {
            return Vector<K>(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
        }

        template <typename K>
        Vector<K> operator-(Vector<K> const &a, Vector<K> const &b)
        {
            return Vector<K>(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
        }

        template <typename K>
        Vector<K> operator-(Vector<K> const &a)
        {
            return Vector<K>(-a.x(), -a.y(), -a.z());
        }

        template <typename K>
        Vector<K> operator*(Vector<K> const &a, typename K::real_t s)
        {
            return Vector<K>(s * a.x(), s * a.y(), s * a.z());
        }

        template <typename K>
        Vector<K> operator*(typename K::real_t s, Vector<K> const &a)
        {
            return Vector<K>(s * a.x(), s * a.y(), s * a.z());
        } 

        template <typename K>
        Vector<K> operator/(Vector<K> const &a, typename K::real_t s)
        {
            return Vector<K>(a.x() / s, a.y() / s, a.z() / s);
        }

        /*! point-wise division */
        template <typename K>
        Vector<K> operator/(Vector<K> const &a, Vector<K> const &b)
        {
            return Vector<K>(a.x() / b.x(), a.y() / b.y(), a.z() / b.z());
        }

        /*! point-wise multiplication */
        template <typename K>
        Vector<K> operator*(Vector<K> const &a, Vector<K> const &b)
        {
            return Vector<K>(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
        }

        /*! vector cross-product. */
        template <typename K>
        Vector<K> operator%(Vector<K> const &a, Vector<K> const &b)
        {
            return Vector<K>(
                a.y() * b.z() - a.z() * b.y(),
                a.z() * b.x() - a.x() * b.z(),
                a.x() * b.y() - a.y() * b.x()
            );
        }
    } // namespace geometry
}} // namespace eScatter

