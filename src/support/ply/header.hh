#pragma once
#include "base.hh"
#include "record-array.hh"

namespace PLY
{
    struct Element
    {
        std::string name;
        RecordSpec  spec;
        size_t      size;

        Element(std::string const &name, RecordSpec const &spec, size_t size):
            name(name), spec(spec), size(size) {}
    };

    class Header: public std::vector<Element>
    {
        public:
            Format format;
            std::vector<std::string> comments;
    };
}

