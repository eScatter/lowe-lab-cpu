#include <iostream>
#include <vector>

#include "command.hh"

using namespace System;

int main(int argc_, char **argv_)
{
    std::vector<std::string> argv(argv_ + 1, argv_ + argc_);
    if (argv.size() > 0)
    {
        if (Command::exists(argv[0]))
        {
            Command::at(argv[0])(argv);
            return 0;
        } 
    }

    Command::at("list")(argv);
    return 1;
}

