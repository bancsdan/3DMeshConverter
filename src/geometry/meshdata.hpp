#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <vector>

#include "triangle.hpp"

struct MeshData
{
    std::vector<Triangle> m_triangles;
};

#endif