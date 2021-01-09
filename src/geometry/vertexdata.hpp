#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <string>
#include "vector3d.hpp"

struct VertexData {
    Vector3d m_pos;
    Vector3d m_normal;
    Vector3d m_texture;
    Vector3d m_color;

    VertexData() = default;
    VertexData(const Vector3d& pos) : m_pos(pos) {}
};

#endif