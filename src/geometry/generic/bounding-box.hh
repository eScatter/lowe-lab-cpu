#pragma once
#include "../../support/misc/iterators.hh"
#include <numeric>

namespace eScatter { namespace geometry
{
    namespace generic
    {
        using System::head;
        using System::tail;

        template <typename K>
        class BoundingBox: public K
        {
            using typename K::Point;
            using typename K::Vector;

            public:
                Point min, max;

                template <typename Range>
                BoundingBox(Range const &points)
                {
                    min = head(points);
                    max = head(points);

                    for (Point const &p : tail(points))
                        insert(p);
                }

                BoundingBox(Point const &p):
                    min(p), max(p) {}

                BoundingBox(Point const &a, Point const &b):
                    min(a), max(b) {}

                Vector extent() const
                    { return max - min; }

                bool inside(Point const &p) const
                {
                    for (unsigned i = 0; i < 3; ++i)
                        if (min[i] > p[i] || max[i] < p[i])
                            return false;
                    return true;
                }

                void insert(Point const &p)
                {
                    min = Point::min(min, p);
                    max = Point::max(max, p);
                }

                BoundingBox &operator+=(BoundingBox const &other)
                {
                    min = Point::min(min, other.min);
                    max = Point::max(max, other.max);
                    return *this;
                }

                BoundingBox operator+(BoundingBox const &other) const
                {
                    return BoundingBox(*this) += other;
                }
        };
    }
}}

