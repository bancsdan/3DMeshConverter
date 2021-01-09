#include <cstdint>
#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include <cctype>
#include <algorithm>
#include <string>
#include <math.h>

#include "utility.hpp"
#include "converter/reader/ireader.hpp"
#include "converter/reader/obj_reader.hpp"
#include "geometry/vector3d.hpp"

class ObjReader;

bool Utility::isLittleEndian()
{
        int16_t i = 1;
        char* p = (char*)&i;
        return p[0] == 1;
}

Utility::InputFormat Utility::convertInputFormatToEnum(const std::string& format)
{
        auto entry = std::find_if(input_formats.begin(), input_formats.end(), [&format](const auto& format_pair) { return format_pair.first == format;});
        if (entry != input_formats.end())
        {
                return entry->second;
        }
        return Utility::InputFormat::INVALID;
}

Utility::OutputFormat Utility::convertOutputFormatToEnum(const std::string& format)
{
        auto entry = std::find_if(output_formats.begin(), output_formats.end(), [&format](const auto& format_pair) { return format_pair.first == format;});
        if (entry != output_formats.end())
        {
                return entry->second;
        }
        return Utility::OutputFormat::INVALID;
}

bool Utility::isSupportedInputFormat(Utility::InputFormat format)
{
    return format != Utility::InputFormat::INVALID;
}

bool Utility::isSupportedOutputFormat(Utility::OutputFormat format)
{
    return format != Utility::OutputFormat::INVALID;
}

void Utility::displayHelp(char* argv[])
{
        std::cout << "Usage: "<< argv[0] <<" <inputfile> <outputfile>" << std::endl << std::endl;
        
        std::cout << "Currently supported input filetypes:" << std::endl;
        for (const auto& format_pair : input_formats)
        {
                std::cout << "\t." << format_pair.first << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Currently supported output filetypes:" << std::endl;
        for (const auto format_pair : output_formats)
        {
                std::cout << "\t." << format_pair.first << std::endl;
        }
        std::cout << std::endl;
}
