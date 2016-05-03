#pragma once
#include <array>
#include <vector>
#include "../numeric/tabulated.hh"

namespace cornell { 
    using eScatter::numeric::Tabulated;

    /*! \brief Colour management.
     *
     * The Cornell module is a full spectrum simulator. To generate accurate
     * colours from a spectrum of light, we determine the CIE X-Y-Z
     * coordinates. For each of these coordinates we have a tabulated response
     * function \f$\bar{x}(\lambda)\f$, \f$\bar{y}(\lambda)\f$, and
     * \f$\bar{z}(\lambda)\f$. To compute the respective coordinate, we
     * integrate 
     *  \f[
     *      X = \int_{0.39}^{0.83} \bar{x}(\lambda) P(\lambda) {\rm d}\lambda.
     *  \f]
     * 
     * The XYZ coordinates span a three-dimensional colour space that has been
     * tuned to match human perception one-to-one. This means that colours with
     * different coordinates will seem different to a human observer, and vice
     * versa if an observer spots a difference the XYZ values must be
     * different.
     *
     * Because the function-space, that these coordinates operate in, is
     * linear, any linear combination of light intensities from three different
     * coloured lights will fill a triangle within the space of XYZ
     * coordinates. In particular, we have in mind the set of red, green and
     * blue, commonly present in popular display devices. This triangle is
     * known as the _gamut_. The technology used in computer displays,
     * laserjets and photo printers limits the range of displayable colours to
     * their own gamut (which is different for every device). If we store the 
     * original XYZ information, we may some day enjoy the full glory of 
     * colours generated here.
     */
    namespace colour {
        extern std::vector<std::array<float, 4>> cie2012_data;

        extern Tabulated<float> cie2012_X;
        extern Tabulated<float> cie2012_Y;
        extern Tabulated<float> cie2012_Z;
    }
}

