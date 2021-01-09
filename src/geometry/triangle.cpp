#include <math.h>
#include <iostream>

#include "triangle.hpp"
#include "vertexdata.hpp"

Triangle::Triangle(const VertexData& a, const VertexData& b, const VertexData& c) : m_a(a), m_b(b), m_c(c)
{    
}

double Triangle::GetArea() const noexcept
{
    const double a_side = (m_b.m_pos - m_a.m_pos).GetLength();
    const double b_side = (m_c.m_pos - m_b.m_pos).GetLength();
    const double c_side = (m_a.m_pos - m_c.m_pos).GetLength();
    const double s = (a_side + b_side + c_side) / 2.0;
    return sqrt(s * (s - a_side) * (s - b_side) * (s - c_side));
}