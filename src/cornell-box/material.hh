#pragma once
#include "diffuse.hh"
#include "emission.hh"
#include "refraction.hh"
#include "specular.hh"
#include "black-body.hh"
#include "sensor.hh"

namespace cornell
{
    /*! \brief Collection of materials. */
    namespace material
    {
        extern std::map<std::string, SellmeierEquation> sellmeier_db;

        extern RefractionInterface glass_BK7;

        extern DiffuseInterface diffuse_white,
                                diffuse_red,
                                diffuse_green,
                                diffuse_blue;

        extern SpecularInterface mirror;

        extern EmissionInterface sunlight;

        extern SensorInterface sensor;
    }
}

