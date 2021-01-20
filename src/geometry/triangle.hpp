#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <Eigen/Dense>
#include <optional>

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
  bool isInside(const Eigen::Vector4d &point) const;
  std::optional<Eigen::Vector4d>
  rayIntersection(const Eigen::Vector4d &ray_starting_point,
                  const Eigen::Vector4d &ray_direction) const;
  void transform(const Eigen::Matrix4d &transform_matrix,
                 const Eigen::Matrix4d &transform_matrix_for_normal);
};

} // namespace Converter

#endif