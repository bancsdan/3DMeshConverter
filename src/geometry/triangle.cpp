#include <Eigen/Dense>
#include <optional>

#include "triangle.hpp"
#include "utility.hpp"
#include "vertexdata.hpp"

namespace Converter {

Triangle::Triangle(const VertexData &a, const VertexData &b,
                   const VertexData &c)
    : a(a), b(b), c(c) {}

double Triangle::getArea() const {
  const auto ab_side = b.pos - a.pos;
  const auto ac_side = c.pos - a.pos;
  const auto cross = ab_side.cross3(ac_side);
  return cross.norm() / 2.0;
}

Eigen::Vector4d Triangle::getNormal() const {
  const auto ab_side = b.pos - a.pos;
  const auto ac_side = c.pos - a.pos;
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

bool Triangle::isInside(const Eigen::Vector4d &point) const {
  const auto &triangle_normal = getNormal();

  if (!Utility::isEqual((a.pos - point).dot(triangle_normal), 0.0)) {
    return false;
  }

  const bool is_inside_ab =
      (b.pos - a.pos).cross3(point - a.pos).dot(triangle_normal) >= 0.0;
  const bool is_inside_bc =
      (c.pos - b.pos).cross3(point - b.pos).dot(triangle_normal) >= 0.0;
  const bool is_inside_ca =
      (a.pos - c.pos).cross3(point - c.pos).dot(triangle_normal) >= 0.0;

  return is_inside_ab && is_inside_bc && is_inside_ca;
}

std::optional<Eigen::Vector4d>
Triangle::rayIntersection(const Eigen::Vector4d &ray_starting_point,
                          const Eigen::Vector4d &ray_direction) const {
  const auto triangle_normal = getNormal();

  const double d = triangle_normal.dot(a.pos);
  const double det = triangle_normal.dot(ray_direction);

  if (Utility::isEqual(det, 0.0)) {
    return {};
  }

  const double t = (d - triangle_normal.dot(ray_starting_point)) / det;
  if (t < 0) {
    return {};
  }

  const auto intersection_point =
      ray_starting_point + t * ray_direction;

  if (isInside(intersection_point)) {
	return {intersection_point};  
  }
  return {};
}

void Triangle::transform(const Eigen::Matrix4d &transform_matrix,
                         const Eigen::Matrix4d &transform_matrix_for_normal) {
  Utility::transformVector(a.pos, transform_matrix);
  Utility::transformVector(b.pos, transform_matrix);
  Utility::transformVector(c.pos, transform_matrix);

  Utility::transformVector(a.normal, transform_matrix_for_normal);
  Utility::transformVector(b.normal, transform_matrix_for_normal);
  Utility::transformVector(c.normal, transform_matrix_for_normal);

  a.normal.normalize();
  b.normal.normalize();
  c.normal.normalize();
}

} // namespace Converter