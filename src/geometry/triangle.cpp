#include <Eigen/Dense>
#include <iostream>
#include <math.h>

#include "triangle.hpp"
#include "vertexdata.hpp"

namespace Converter {

Triangle::Triangle(const VertexData &a, const VertexData &b,
                   const VertexData &c)
    : m_a(a), m_b(b), m_c(c) {}

double Triangle::getArea() const {
  const auto &ab_side = m_b.m_pos - m_a.m_pos;
  const auto &ac_side = m_c.m_pos - m_a.m_pos;
  const auto &cross = ab_side.cross3(ac_side);
  return cross.norm() / 2.0;
}

Eigen::Vector4d Triangle::getNormal() const {
  const auto &ab_side = m_b.m_pos - m_a.m_pos;
  const auto &ac_side = m_c.m_pos - m_a.m_pos;
  auto cross = ab_side.cross3(ac_side);
  cross.normalize();
  return cross;
}

bool Triangle::operator==(const Triangle &other) const {
  return m_a.m_pos.isApprox(other.m_a.m_pos) &&
         m_b.m_pos.isApprox(other.m_b.m_pos) &&
         m_c.m_pos.isApprox(other.m_c.m_pos) &&
         m_a.m_normal.isApprox(other.m_a.m_normal) &&
         m_b.m_normal.isApprox(other.m_b.m_normal) &&
         m_c.m_normal.isApprox(other.m_c.m_normal);
}

} // namespace Converter