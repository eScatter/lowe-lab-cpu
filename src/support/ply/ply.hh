#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <vector>
#include <typeinfo>
#include <stdexcept>

#include "base.hh"
#include "header.hh"
#include "io.hh"
#include "record-print.hh"

namespace PLY
{
    /*! PLY data class
     *
     * Used for reading and writing PLY files. This class stores both
     * the header of the PLY and a dictionary of binary data blobs.
     * Each binary blob corresponds to an `element' in the PLY file.
     * An element contains one or more `properties'. These properties
     * are represented as fields in a RecordArray. The RecordArray can
     * be iterated over, yielding any compatible type of tuple or array.
     */
    class PLY
    {
        Header header_;

        std::map<std::string, RecordArray> data_;

        public:
            /*! constructor, reads data from a file. */
            PLY(std::string const &file_name);

            /*! get the format (ascii or binary) of the PLY. */
            Format const &format() const
                { return header_.format; }

            /*! set the format (ascii or binary) of the PLY. */
            void format(Format fmt)
                { header_.format = fmt; }

            /*! look at the header of the PLY. */
            Header const &header() const
                { return header_; }

            /*! retrieve element data. */
            RecordArray const &operator[](std::string const &key)
                { return data_.at(key); }

            /*! add a line of comment to the header. */
            PLY &comment(std::string const &msg)
                { header_.comments.push_back(msg); return *this; }
    };
}

