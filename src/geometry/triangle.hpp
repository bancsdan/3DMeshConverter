#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <Eigen/Dense>

#include "vertexdata.hpp"

namespace Converter {

class Triangle {
public:
  VertexData a;
  VertexData b;
  VertexData c;

  Triangle() = default;
  Triangle(const VertexData &a, const VertexData &b, const VertexData &c);

  double getArea() const;
  Eigen::Vector4d getNormal() const;
  bool operator==(const Triangle &other) const;
};

} // namespace Converter

#endif