#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace eScatter { namespace geometry
{
    namespace bvh
    {
        template <typename K>
        struct FlatNode
        {
            using BoundingBox = typename K::BoundingBox;
          
            BoundingBox bounding_box;

            // begin and end of elements in data_
            uint32_t begin, end;

            // offset of second child into flat_nodes_
            uint32_t right_offset;

            inline bool is_leaf() const { return right_offset == 0; }

            FlatNode(BoundingBox const &bb, uint32_t begin, uint32_t end, uint32_t right_offset)
                : bounding_box(bb), begin(begin), end(end), right_offset(right_offset) {}
        };

        template <typename K>
        struct IntersectionInfo
        {
            typename K::real_t time;
            K *object = nullptr;
        };

        template <typename K>
        class Tree
        {
            using Ray = typename K::Ray;
            using real_t = typename K::real_t;
            using BoundingBox = typename K::BoundingBox;
            // using ObjectPtr = std::unique_ptr<K>;

            uint32_t n_nodes_, n_leaves_, leaf_size_;
            std::unique_ptr<std::vector<K>> data_;
            std::vector<FlatNode<K>> flat_nodes_;

            public:
                Tree(std::unique_ptr<std::vector<K>> &&data, uint32_t leaf_size = 4);

                void build();

                bool find_intersection(
                    Ray const &ray, IntersectionInfo<K> &info, 
                    bool occlusion, real_t epsilon) const;

                uint32_t number_of_nodes() const { return n_nodes_; }
                uint32_t number_of_leaves() const { return n_leaves_; }
        };

        template <typename K>
        Tree<K>::Tree(std::unique_ptr<std::vector<K>> &&data, uint32_t leaf_size):
            n_nodes_(0), n_leaves_(0), leaf_size_(leaf_size), data_(std::move(data))
        {
            //for (auto &obj : range)
            //    data_.push_back(std::move(obj));

            build();
        }
    } // namespace bvh
}} // namespace eScatter::geometry

#include "build.inc"
#include "traverse.inc"

