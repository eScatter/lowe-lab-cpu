#include "colour.hh"
#include "../support/map.hh"

using namespace cornell;
using namespace eScatter;

Tabulated<float> colour::cie2012_X(
    lazy_map(cie2012_data, [] (std::array<float, 4> const &a) { return a[1]; }), 
    0.390, 0.830, 0.001);

Tabulated<float> colour::cie2012_Y(
    lazy_map(cie2012_data, [] (std::array<float, 4> const &a) { return a[2]; }), 
    0.390, 0.830, 0.001);

Tabulated<float> colour::cie2012_Z(
    lazy_map(cie2012_data, [] (std::array<float, 4> const &a) { return a[3]; }), 
    0.390, 0.830, 0.001);

