#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>

namespace Utility {
    // if system is big endian will need to reverse order when writing stl file
    bool   IsLittleEndian();
}

#endif