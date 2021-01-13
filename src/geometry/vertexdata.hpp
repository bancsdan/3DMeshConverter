#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <string>
#include <Eigen/Dense>

struct VertexData {
    Eigen::Vector4d m_pos{0.0, 0.0, 0.0, 0.0};
    Eigen::Vector4d m_normal{0.0, 0.0, 0.0, 0.0};
    Eigen::Vector4d m_texture{0.0, 0.0, 0.0, 0.0};

    VertexData() = default;
    VertexData(const Eigen::Vector4d& pos) : m_pos(pos) {}
};

#endif