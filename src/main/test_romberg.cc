#include "command.hh"
#include "../numeric/romberg.hh"
#include "../numeric/tabulated.hh"
#include "../cornell-box/black-body.hh"
#include "../cornell-box/rng.hh"
#include "../cornell-box/colour.hh"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace eScatter;
using namespace numeric;
using namespace cornell;

Command cmd_test_blackbody("planck", "test black body radiator",
    [] (std::vector<std::string> const &args_)
{
    /*BlackBody<double> f(Rng::generator(), 5000);
    for (unsigned i = 0; i < 1000000; ++i)
    {
        std::cout << f() << std::endl;
    }*/

    for (double a = 0.39; a <= 0.83; a += 0.01)
    {
        std::cout << a << " " 
          << colour::cie2012_X(a) << " "
          << colour::cie2012_Y(a) << " "
          << colour::cie2012_Z(a) << std::endl;
    }

    return 0;
});

