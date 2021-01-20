#include <Eigen/Dense>
#include <algorithm>
#include <cmath>
#include <vector>

#include "meshdata.hpp"

namespace Converter {

double MeshData::calculateSurfaceArea() const {
  double surface_area = 0.0;
  for (const auto &triangle : triangles) {
    surface_area += triangle.getArea();
  }
  return surface_area;
}

double MeshData::calculateVolume() const {
  double volume = 0.0;
  for (const auto &triangle : triangles) {
    volume += triangle.a.pos.cross3(triangle.b.pos).dot(triangle.c.pos);
  }
  return std::abs(volume / 6.0);
}

bool MeshData::isPointInside(const Eigen::Vector4d &point) const {
  std::vector<Eigen::Vector4d> intersections;

  for (const auto &triangle : triangles) {
    if (triangle.isInside(point)) {
      return true;
    }

    const auto &intersection =
        triangle.rayIntersection(point, {0.0, 1.0, 0.0, 0.0});

    if (intersection) {

      const auto &predicate = [&intersection](const auto &point) {
        const auto &i_point = intersection.value();
        return point.isApprox(i_point);
      };

      if (std::find_if(intersections.begin(), intersections.end(), predicate) ==
          intersections.end()) {
        intersections.push_back(intersection.value());
      }
    }
  }
  return intersections.size() % 2 == 1;
}

void MeshData::transform(const Eigen::Matrix4d &translation_matrix,
                         const Eigen::Matrix4d &rotation_matrix,
                         const Eigen::Matrix4d &scale_matrix) {
  const Eigen::Matrix4d &transformation_matrix =
      translation_matrix * rotation_matrix * scale_matrix;
  const Eigen::Matrix4d &normal_transformation_matrix =
      (rotation_matrix * scale_matrix).inverse().transpose();

  for (auto &triangle : triangles) {
    triangle.transform(transformation_matrix, normal_transformation_matrix);
  }
}

} // namespace Converter