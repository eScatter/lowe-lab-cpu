#pragma once
#include "ndrange.hh"

namespace eScatter { namespace numeric
{
    template <unsigned D>
    class Slice
    {
        public:
            size_t offset, size;
            shape_t<D> shape;
            stride_t<D> stride;

            Slice(shape_t<D> const &shape):
                offset(0), size(calc_size<D>(shape)),
                shape(shape),
                stride(calc_stride<D>(shape))
            {
            }

            Slice(size_t offset, shape_t<D> const &shape, stride_t<D> const &stride):
                offset(offset), size(calc_size<D>(shape)),
                shape(shape),
                stride(stride)
            {}

            size_t flat_index(shape_t<D> const &x)
            {
                size_t i = offset;
                for (unsigned i = 0; i < D; ++i)
                    i += x[i] * stride[i];
                return i;
            }

            Slice<D> transpose() const // reverse axes
            {
                stride_t<D> new_stride;
                for (unsigned i = 0; i < D; ++i)
                    new_stride[D-i-1] = stride[i];
                return Slice<D>(offset, shape, new_stride);
            }

            template <unsigned axis>
            Slice<D> sub(size_t begin, size_t end, size_t step = 1)
            {
                size_t new_offset = offset + begin * stride[axis];
                stride_t<D> new_stride = stride;
                shape_t<D> new_shape = shape;
                new_stride[axis] *= step;
                new_shape[axis] = (end - begin) / abs(step);
                return Slice<D>(new_offset, new_shape, new_stride);
            }

            template <unsigned axis>
            Slice<D> reverse()
            {
                size_t new_offset = offset + stride[axis] * (shape[axis] - 1);
                stride_t<D> new_stride = stride;
                new_stride[axis] = -stride[axis];
                return Slice<D>(new_offset, shape, new_stride);
            }

            NdRange<D> begin() const
            {
                return NdRange<D>(offset, shape, stride);
            }

            NdRange<D> end() const
            {
                return NdRange<D>();
            }
    };
}} // namespace numeric

