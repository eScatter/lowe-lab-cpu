#include "../main/command.hh"
#include "../main/argparse.hh"

#include "cornell.hh"
#include "colour.hh"


using argparse::Args;
using argparse::Option;

/*! \brief The Cornell box
 *
 * Renders a scene varying on the Cornell box.
 */
    class Scene
    {

    };

}

Command cmd_cornell(
    "cornell",
    "Renders the Cornell box (or a version thereof). This box has four material "
    "types: light emission, diffuse scattering, specular reflection and "
    "transparent refraction. The light source emits a predifined spectrum. A "
    "diffuse surface absorbs a certain fraction as function of wavelength. "
    "Refracting surface has a certain refraction index. Specular reflection is "
    "parameter free.",
    [] (std::vector<std::string> const &args_) -> int
{
    return 0;
});

