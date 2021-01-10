#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <vector>

class Triangle;

struct MeshData
{
    std::vector<Triangle> m_triangles;
};

#endif