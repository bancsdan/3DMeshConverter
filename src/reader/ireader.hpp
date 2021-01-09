#ifndef IREADER_HPP
#define IREADER_HPP

#include <memory>

#include "utility.hpp"

class IReader
{
public:
    static std::unique_ptr<IReader> createReader(Utility::InputFormat format);
};

#endif