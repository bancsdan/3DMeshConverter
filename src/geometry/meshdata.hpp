#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <vector>
#include <string>

#include "triangle.hpp"

struct MeshData
{
    std::string m_material_file;
    std::vector<Triangle> m_triangles;
};

#endif