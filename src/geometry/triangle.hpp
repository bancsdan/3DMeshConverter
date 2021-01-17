#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <Eigen/Dense>

#include "vertexdata.hpp"

namespace Converter {

class Triangle {
public:
  VertexData m_a;
  VertexData m_b;
  VertexData m_c;

  Triangle() = default;
  Triangle(const VertexData &a, const VertexData &b, const VertexData &c);

  double getArea() const;
  Eigen::Vector4d getNormal() const;
};

} // namespace Converter

#endif