#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace Utility {
    // if system is big endian will need to reverse order when writing stl file
    bool isLittleEndian();
    void displayHelp(char* argv[]);
    inline bool isEqual(double a, double b, double epsilon = 0.00000001) { return fabs(a - b) < epsilon; }
}

#endif