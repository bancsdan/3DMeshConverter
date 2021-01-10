#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace Utility {
    // if system is big endian will need to reverse order when writing stl file
    bool isLittleEndian();
    void displayHelp(char* argv[]);
}

#endif