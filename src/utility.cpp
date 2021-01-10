#include <cstdint>
#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include <cctype>
#include <algorithm>
#include <string_view>
#include <math.h>

#include "utility.hpp"
#include "reader/supported_input_formats.hpp"
#include "writer/supported_output_formats.hpp"
#include "geometry/vector3d.hpp"

bool Utility::isLittleEndian()
{
        int16_t i = 1;
        char* p = (char*)&i;
        return p[0] == 1;
}

void Utility::displayHelp(char* argv[])
{
        std::cout << "Usage: "<< argv[0] <<" <inputfile> <outputfile>" << std::endl << std::endl;
        
        std::cout << "Currently supported input filetypes:" << std::endl;
        for (const auto& format_pair : Reader::supported_input_formats_map)
        {
                std::cout << "\t." << format_pair.first << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Currently supported output filetypes:" << std::endl;
        for (const auto format_pair : Writer::supported_output_formats_map)
        {
                std::cout << "\t." << format_pair.first << std::endl;
        }
        std::cout << std::endl;
}
