#include <fstream>
#include <iostream>
#include <string>

#include "obj_reader.hpp"
#include "geometry/meshdata.hpp"
#include "exception.hpp"
#include "utility.hpp"

MeshData ObjReader::read(const std::string& file_name)
{
    std::ifstream in_file_stream;
    in_file_stream.open(file_name);
    if (!in_file_stream)
    {
        throw FileNotFoundException();
    }

    for (std::string line; std::getline(in_file_stream, line); )
    {
        std::cout << line << '\n';
        auto lineVect = Utility::splitString(line, ' ');

        if (!lineVect.empty())
        {
            if(lineVect[0].rfind("f", 0) == 0)
            {
                std::cout << true << '\n';
            }
            else
            {
                std::cout << false << '\n';
            }
            
        }

    }



    return MeshData{};
}