#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "exception.hpp"
#include "geometry/meshdata.hpp"
#include "reader/supported_input_formats.hpp"
#include "utility.hpp"
#include "writer/supported_output_formats.hpp"

namespace Converter {

namespace Utility {

void displaySupportedFormats() {
  std::cout << "Currently supported input filetypes:" << std::endl;
  for (const auto &format_pair : Reader::supported_input_formats_map) {
    std::cout << "\t" << format_pair.first << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Currently supported output filetypes:" << std::endl;
  for (const auto format_pair : Writer::supported_output_formats_map) {
    std::cout << "\t" << format_pair.first << std::endl;
  }
  std::cout << std::endl;
}

std::string toLower(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](std::string::value_type c) {
                   return static_cast<std::string::value_type>(std::tolower(c));
                 });
  return str;
}

std::vector<std::string> splitString(const std::string &str) {
  std::istringstream buffer(str);
  std::vector<std::string> result{std::istream_iterator<std::string>(buffer),
                                  std::istream_iterator<std::string>()};
  return result;
}

bool startsWith(const std::string &str, const char *start) {
  return str.rfind(start, 0U) == 0U;
}

double calculateMeshSurfaceArea(const MeshData &mesh) {
  double surface_area = 0.0;
  for (const auto &triangle : mesh.triangles) {
    surface_area += triangle.getArea();
  }
  return surface_area;
}

double calculateMeshVolume(const MeshData &mesh) {
  double volume = 0.0;
  for (const auto &triangle : mesh.triangles) {
    volume += triangle.a.pos.cross3(triangle.b.pos).dot(triangle.c.pos);
  }
  return std::abs(volume / 6.0);
}

bool isPointInsideMesh(const MeshData &mesh, const Eigen::Vector4d &point) {
  std::vector<Eigen::Vector4d> intersections;

  for (const auto &triangle : mesh.triangles) {

    if (isInsideTriangle(point, triangle)) {
      return true;
    }

    const auto &intersection =
        rayTriangleIntersection(point, {0.0, 1.0, 0.0, 0.0}, triangle);

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

std::optional<Eigen::Vector4d>
rayTriangleIntersection(const Eigen::Vector4d &ray_starting_point,
                        const Eigen::Vector4d &ray_direction,
                        const Triangle &triangle) {
  const auto &triangle_normal = triangle.getNormal();

  const double d = triangle_normal.dot(triangle.a.pos);
  const double det = triangle_normal.dot(ray_direction.normalized());

  if (isEqual(det, 0.0)) {
    return {};
  }

  const double t = (d - triangle_normal.dot(ray_starting_point)) / det;

  if (t < 0) {
    return {};
  }

  const auto &intersection_point =
      ray_starting_point + t * ray_direction.normalized();

  if (isInsideTriangle(intersection_point, triangle))
    return {intersection_point};
  return {};
}

bool isInsideTriangle(const Eigen::Vector4d &point, const Triangle &triangle) {
  const auto &a = triangle.a.pos;
  const auto &b = triangle.b.pos;
  const auto &c = triangle.c.pos;
  const auto &triangle_normal = triangle.getNormal();

  if (!isEqual((a - point).dot(triangle_normal), 0.0)) {
    return false;
  }

  const bool is_inside_ab =
      (b - a).cross3(point - a).dot(triangle_normal) >= 0.0;
  const bool is_inside_bc =
      (c - b).cross3(point - b).dot(triangle_normal) >= 0.0;
  const bool is_inside_ca =
      (a - c).cross3(point - c).dot(triangle_normal) >= 0.0;

  return is_inside_ab && is_inside_bc && is_inside_ca;
}

void transformMesh(MeshData &mesh, const Eigen::Matrix4d &translation_matrix,
                   const Eigen::Matrix4d &rotation_matrix,
                   const Eigen::Matrix4d &scale_matrix) {
  const Eigen::Matrix4d &transformation_matrix =
      translation_matrix * rotation_matrix * scale_matrix;
  const Eigen::Matrix4d &normal_transformation_matrix =
      (rotation_matrix * scale_matrix).inverse().transpose();

  for (auto &triangle : mesh.triangles) {
    transformTriangle(triangle, transformation_matrix,
                      normal_transformation_matrix);
  }
}

void transformVector(Eigen::Vector4d &point,
                     const Eigen::Matrix4d &transform_matrix) {
  point = transform_matrix * point;
}

void transformTriangle(Triangle &triangle,
                       const Eigen::Matrix4d &transform_matrix,
                       const Eigen::Matrix4d &transform_matrix_for_normal) {
  transformVector(triangle.a.pos, transform_matrix);
  transformVector(triangle.b.pos, transform_matrix);
  transformVector(triangle.c.pos, transform_matrix);

  transformVector(triangle.a.normal, transform_matrix_for_normal);
  transformVector(triangle.b.normal, transform_matrix_for_normal);
  transformVector(triangle.c.normal, transform_matrix_for_normal);

  triangle.a.normal.normalize();
  triangle.b.normal.normalize();
  triangle.c.normal.normalize();
}

Eigen::Matrix4d getTranslationMatrix(const Eigen::Vector3d &translation) {
  Eigen::Matrix4d translation_matrix;
  translation_matrix.setIdentity();
  translation_matrix(0, 3) = translation.x();
  translation_matrix(1, 3) = translation.y();
  translation_matrix(2, 3) = translation.z();

  return translation_matrix;
}

Eigen::Matrix4d getRotationMatrix(const Eigen::Vector3d &rotation_axis,
                                  double angle) {
  Eigen::Matrix4d rotation_matrix;
  rotation_matrix.setIdentity();
  rotation_matrix.block<3, 3>(0, 0) =
      Eigen::AngleAxisd(angle, rotation_axis.normalized()).matrix();

  return rotation_matrix;
}

Eigen::Matrix4d getScaleMatrix(const Eigen::Vector3d &scale) {
  Eigen::Matrix4d scale_matrix;
  scale_matrix.setIdentity();
  scale_matrix(0, 0) *= scale.x();
  scale_matrix(1, 1) *= scale.y();
  scale_matrix(2, 2) *= scale.z();

  return scale_matrix;
}

} // namespace Utility
} // namespace Converter