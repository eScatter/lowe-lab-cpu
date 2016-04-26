#include "command.hh"
#include "../support/ply/ply.hh"

using PLY::operator<<;

Command cmd_test_ply("ply",
    "Test the functionality of the PLY reader and writer.",
    [] (std::vector<std::string> const &args)
{
    if (args.size() < 3)
    {
        std::cerr << "Give the filename of the PLY file as an argument.\n";
        return 1;
    }

    PLY::PLY bunny(args[2]);
    bunny.format(PLY::ASCII);
    std::cout << bunny.header();
    std::cout << bunny["vertex"];
    std::cout << bunny["face"];

    return 0;
});

