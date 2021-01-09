#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <array>

namespace Utility {
    static constexpr std::array<const char*, 3> supported_input_extensions{
        "obj"
    };

    static constexpr std::array<const char*, 1> supported_output_extensions{
        "stl"
    };

    // if system is big endian will need to reverse order when writing stl file
    bool isLittleEndian();
    bool isSupportedInputFormat(const std::string& format);
    bool isSupportedOutputFormat(const std::string& format);
    void displayHelp(int argc, char* argv[]);
}

#endif