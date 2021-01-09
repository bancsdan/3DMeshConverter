#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vertexdata.hpp"

class Triangle {
public:
    VertexData m_a;
    VertexData m_b;
    VertexData m_c;

    Triangle() = default;
    Triangle(const VertexData& a, const VertexData& b, const VertexData& c);

    double GetArea() const noexcept;
};

#endif