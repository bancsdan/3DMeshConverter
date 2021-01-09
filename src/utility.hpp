#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <array>
#include <string>
#include <memory>
#include <utility>

class IReader;

namespace Utility {
    // Update these when adding new extension
    enum class InputFormat {
        OBJ,
        INVALID
    };

    enum class OutputFormat {
        STL,
        INVALID
    };

    static constexpr std::array<std::pair<const char*, InputFormat>, 1> input_formats {
        std::make_pair("obj", InputFormat::OBJ)
    };

    static constexpr std::array<std::pair<const char*, OutputFormat>, 1> output_formats {
        std::make_pair("stl", OutputFormat::STL)
    };
    // Update until here

    // if system is big endian will need to reverse order when writing stl file
    bool isLittleEndian();
    InputFormat convertInputFormatToEnum(const std::string& format);
    OutputFormat convertOutputFormatToEnum(const std::string& format);
    bool isSupportedInputFormat(Utility::InputFormat format);
    bool isSupportedOutputFormat(Utility::OutputFormat format);
    void displayHelp(char* argv[]);
}

#endif