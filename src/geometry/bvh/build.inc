#include <stack>
#include <algorithm>

namespace eScatter { namespace geometry { namespace bvh
{
    struct build_t
    {
        uint32_t parent, begin, end;
        build_t(uint32_t parent, uint32_t begin, uint32_t end):
            parent(parent), begin(begin), end(end) {}
    };

    template <typename K>
    inline uint32_t max_dim(typename K::Vector const &e)
    {
        return (e[0] > e[1] ? 
              (e[0] > e[2] ? 0 : 2) 
            : (e[1] > e[2] ? 1 : 2));
    }

    template <typename K>
    inline uint32_t split_range(
        std::vector<K> &data_,
        build_t const &entry)
    {
        using real_t = typename K::real_t;
        using Vector = typename K::Vector;
        using BoundingBox = typename K::BoundingBox;

        BoundingBox bc(data_[entry.begin].centroid());
        for (uint32_t i = entry.begin + 1; i < entry.end; ++i)
            bc.insert(data_[i].centroid());

        Vector extent = bc.extent();
        uint32_t split_dim = max_dim<K>(extent);
        real_t split_coord = bc.min[split_dim] + extent[split_dim]/2;

        auto mid_ptr = std::partition(
            data_.data() + entry.begin, data_.data() + entry.end,
            [split_dim, split_coord] (K const &a)
            { return a.centroid()[split_dim] < split_coord; });

        return mid_ptr - data_.data();
    }

    template <typename K>
    void Tree<K>::build()
    {
        // magic numbers
        uint32_t const untouched     = 0xFFFFFFFF;
        uint32_t const touched_twice = 0xFFFFFFFD;
        uint32_t const root_node     = 0xFFFFFFFC;

        std::stack<build_t> todo;

        todo.emplace(root_node, 0, data_->size());

        flat_nodes_.reserve(data_->size() * 2);

        while (!todo.empty())
        {
            build_t entry = todo.top();
            todo.pop();

            // compute bounding boxes
            BoundingBox bb(data_->at(entry.begin).bounding_box());
            for (uint32_t i = entry.begin + 1; i < entry.end; ++i)
                bb += data_->at(i).bounding_box();

            // set to leaf node if number of objects is small
            uint32_t size = entry.end - entry.begin;
            uint32_t right_offset = untouched;
            if (size <= leaf_size_)
            {
                right_offset = 0;
                ++n_leaves_;
            }

            // add the node to the list, right_offset will be set by second child
            ++n_nodes_;
            flat_nodes_.emplace_back(bb, entry.begin, entry.end, right_offset);

            // update second child reference in parent
            if (entry.parent != root_node)
            {
                FlatNode<K> &parent = flat_nodes_[entry.parent];

                if (--parent.right_offset == touched_twice)
                    parent.right_offset = n_nodes_ - 1 - entry.parent;
            }

            if (right_offset == 0)
                continue;

            // prepare next steps
            uint32_t mid = split_range(*data_, entry);
            todo.emplace(n_nodes_ - 1, mid, entry.end);
            todo.emplace(n_nodes_ - 1, entry.begin, mid);
        }

        flat_nodes_.shrink_to_fit();
    }
}}} // namespace eScatter::geometry::bvh

/* vim: set filetype=cpp: */
