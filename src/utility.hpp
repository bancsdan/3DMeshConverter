#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <vector>

namespace Utility {
    // if system is big endian will need to reverse order when writing stl file
    bool isLittleEndian();
    void displayHelp(char* argv[]);
    inline bool isEqual(double a, double b, double epsilon = 0.00000001) { return fabs(a - b) < epsilon; }
    std::string toLower(std::string str);
    std::vector<std::string> splitString(const std::string& str, std::string::value_type delim);
    bool startsWith(const std::string& str, const char* start);
}

#endif