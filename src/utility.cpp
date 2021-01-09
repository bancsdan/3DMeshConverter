#include <cstdint>
#include <iostream>
#include <array>
#include <math.h>

#include "utility.hpp"
#include "geometry/vector3d.hpp"

bool Utility::isLittleEndian()
{
        int16_t i = 1;
        char* p = (char*)&i;
        return p[0] == 1;
}

bool Utility::isSupportedInputFormat(const std::string& format)
{
    for (const auto ext : supported_input_extensions)
    {
        if (format == ext)
        {
            return true;
        }
    }
    return false;
}

bool Utility::isSupportedOutputFormat(const std::string& format)
{
    for (const auto ext : supported_output_extensions)
    {
        if (format == ext)
        {
            return true;
        }
    }
    return false;
}

void Utility::displayHelp(int argc, char* argv[])
{
        std::cout << "Usage: "<< argv[0] <<" <inputfile> <outputfile>" << std::endl << std::endl;
        
        std::cout << "Currently supported input filetypes:" << std::endl;
        for (const auto ext : supported_input_extensions)
        {
                std::cout << "\t" << ext << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Currently supported output filetypes:" << std::endl;
        for (const auto ext : supported_output_extensions)
        {
                std::cout << "\t" << ext << std::endl;
        }
        std::cout << std::endl;
}