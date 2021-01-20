#include <Eigen/Dense>
#include <iostream>
#include <math.h>

#include "triangle.hpp"
#include "vertexdata.hpp"

namespace Converter {

Triangle::Triangle(const VertexData &a, const VertexData &b,
                   const VertexData &c)
    : a(a), b(b), c(c) {}

double Triangle::getArea() const {
  const auto &ab_side = b.pos - a.pos;
  const auto &ac_side = c.pos - a.pos;
  const auto &cross = ab_side.cross3(ac_side);
  return cross.norm() / 2.0;
}

Eigen::Vector4d Triangle::getNormal() const {
  const auto &ab_side = b.pos - a.pos;
  const auto &ac_side = c.pos - a.pos;
  auto cross = ab_side.cross3(ac_side);
  cross.normalize();
  return cross;
}

bool Triangle::operator==(const Triangle &other) const {
  return a.pos.isApprox(other.a.pos) && b.pos.isApprox(other.b.pos) &&
         c.pos.isApprox(other.c.pos) && a.normal.isApprox(other.a.normal) &&
         b.normal.isApprox(other.b.normal) &&
         c.normal.isApprox(other.c.normal) &&
         a.texture.isApprox(other.a.texture) &&
         b.texture.isApprox(other.b.texture) &&
         c.texture.isApprox(other.c.texture);
}

} // namespace Converter