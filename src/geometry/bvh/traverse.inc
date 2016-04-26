#include <limits>
#include <stack>

#include "../generic/intersect-bounding-box.hh"

namespace eScatter { namespace geometry { namespace bvh
{
    using eScatter::geometry::generic::intersect;

    template <typename K>
    struct traversal_t
    {
        using real_t = typename K::real_t;

        uint32_t node_idx;
        real_t min_time;

        traversal_t(uint32_t node_idx, real_t min_time):
            node_idx(node_idx), min_time(min_time) {}
    };

    template <typename K>
    inline bool find_object_intersection(
        typename K::Ray const &ray,
        K &obj, 
        IntersectionInfo<K> &info,
        bool occlusion,
        typename K::real_t epsilon)
    {
        IntersectionInfo<K> current;
        current.object = &obj;
        bool hit = obj.intersect(ray, current.time, epsilon);

        if (hit)
        {
            if (occlusion) return true;

            if (current.time < info.time)
                info = current;
        }

        return false;
    }

    template <typename K>
    bool Tree<K>::find_intersection(
        typename K::Ray const &ray, 
        IntersectionInfo<K> &info,
        bool occlusion,
        typename K::real_t epsilon) const
    {
        real_t const inf = std::numeric_limits<real_t>::infinity();
        // info.time = max_t;
        // info.object = nullptr;

        std::stack<traversal_t<K>> todo;
        todo.emplace(0, -inf);

        while (!todo.empty())
        {
            traversal_t<K> entry = todo.top();
            todo.pop();

            if (entry.min_time > info.time)
                continue;

            FlatNode<K> const &node = flat_nodes_[entry.node_idx];

            if (node.is_leaf())
            {
                for (uint32_t i = node.begin; i < node.end; ++i)
                    if (find_object_intersection<K>(ray, data_->at(i), info, occlusion, epsilon))
                        return true;
            }
            else
            {
                real_t time_11, time_12, time_21, time_22;
                uint32_t first  = entry.node_idx + 1,
                         second = entry.node_idx + node.right_offset;

                bool hitc1 = intersect<K>(flat_nodes_[first ].bounding_box, ray, time_11, time_12);
                bool hitc2 = intersect<K>(flat_nodes_[second].bounding_box, ray, time_21, time_22);

                if (hitc1 && hitc2)
                {
                    if (time_21 < time_11)
                    {
                        std::swap(time_11, time_21);
                        std::swap(time_12, time_22);
                        std::swap(first, second);
                    }

                    todo.emplace(second, time_21);
                    todo.emplace(first,  time_11);
                }

                else if (hitc1)
                {
                    todo.emplace(first, time_11);
                }

                else if (hitc2)
                {
                    todo.emplace(second, time_21);
                }
            }
        }
        
        return (info.object != nullptr);
    }
}}} // namespace eScatter::geometry::bvh

/* vim: set filetype=cpp: */
