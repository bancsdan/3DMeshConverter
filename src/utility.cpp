#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>
#include <algorithm>
#include <string>
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

std::string Utility::toLower(std::string str)
{
        std::transform(str.begin(), str.end(), str.begin(), [](std::string::value_type c){ return static_cast<std::string::value_type>(std::tolower(c)); });
        return str;
}

std::vector<std::string> Utility::splitString(const std::string& str, std::string::value_type delim)
{
        std::vector<std::string> result;
        std::string::size_type start = 0;
        std::string::size_type end = 0;

        while((end = str.find(delim, start)) != std::string::npos)
        {
                const std::string word = str.substr(start, end);
                result.push_back(word);
                start = end + 1;
        }

        return result;
}