#include <math.h>
#include <Eigen/Dense>
#include <iostream>

#include "triangle.hpp"
#include "vertexdata.hpp"

namespace Converter {

Triangle::Triangle(const VertexData& a, const VertexData& b,
                   const VertexData& c)
    : m_a(a), m_b(b), m_c(c) {}

double Triangle::getArea() const {
  const auto& a_side = m_b.m_pos - m_a.m_pos;
  const auto& b_side = m_c.m_pos - m_b.m_pos;
  const auto& cross = a_side.cross3(b_side);
  return cross.norm() / 2.0;
}

}  // namespace Converter