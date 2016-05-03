#include "material.hh"
#include <functional>
#include <map>
#include <string>

using namespace cornell;

std::function<real_t (real_t)> gauss_profile(real_t mean, real_t fwhm)
{
    real_t v = fwhm*fwhm * 0.36067376022224085;
    return [mean, v] (real_t l)
    {
        real_t x = l - mean;
        return exp(-x * x / v);
    };
}

std::map<std::string, SellmeierEquation> material::sellmeier_db = {
    {"glass:BK7", { 1.03961212, 0.00600069867, 
                    0.231792344, 0.0200179144, 
                    1.01046945, 103.560653 } }
};

RefractionInterface material::glass_BK7(sellmeier_db["glass:BK7"]);

DiffuseInterface material::diffuse_white([] (real_t l) { return 1.0; }),
                 material::diffuse_red(gauss_profile(0.6, 0.03)),
                 material::diffuse_green(gauss_profile(0.52, 0.03)),
                 material::diffuse_blue(gauss_profile(0.47, 0.03));

SpecularInterface material::mirror;

EmissionInterface material::sunlight(black_body_icdf(5000.0));

SensorInterface material::sensor;

