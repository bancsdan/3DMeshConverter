#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <string>
#include <Eigen/Dense>

struct VertexData {
    Eigen::Vector4d m_pos;
    Eigen::Vector4d m_normal;
    Eigen::Vector4d m_texture;

    VertexData() = default;
    VertexData(const Eigen::Vector4d& pos) : m_pos(pos) {}
};

#endif