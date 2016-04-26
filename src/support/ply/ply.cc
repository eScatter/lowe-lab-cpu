#include "ply.hh"

using namespace PLY;

PLY::PLY::PLY(std::string const &file_name)
{
    std::ifstream fi(file_name, std::ios::binary);
    fi >> header_;

    for (auto const &element : header_)
    {
        data_[element.name] = RecordArray(element.spec, fi, element.size);
    }
}


