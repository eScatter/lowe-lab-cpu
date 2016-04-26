#pragma once
#include "ndarray.hh"

namespace eScatter { namespace numeric
{
    extern NdArray<size_t, 2> hilbert_array(unsigned n);
    extern std::vector<size_t> hilbert_walk(unsigned n);
}}

