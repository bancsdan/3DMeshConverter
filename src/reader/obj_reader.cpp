#include <fstream>
#include <iostream>

#include "obj_reader.hpp"
#include "geometry/meshdata.hpp"
#include "exception.hpp"

MeshData ObjReader::read(const std::string& file_name)
{
    std::ifstream in_file;
    in_file.open(file_name);
    if (!in_file)
    {
        throw FileNotFoundException();
    }

    return MeshData{};
}