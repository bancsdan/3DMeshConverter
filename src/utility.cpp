#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "geometry/meshdata.hpp"
#include "reader/supported_input_formats.hpp"
#include "utility.hpp"
#include "writer/supported_output_formats.hpp"

namespace Converter {

namespace Utility {

void displayHelp(char *argv[]) {
  std::cout << "Usage: " << argv[0] << " <inputfile> <outputfile>" << std::endl
            << std::endl;

  std::cout << "Currently supported input filetypes:" << std::endl;
  for (const auto &format_pair : Reader::supported_input_formats_map) {
    std::cout << "\t." << format_pair.first << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Currently supported output filetypes:" << std::endl;
  for (const auto format_pair : Writer::supported_output_formats_map) {
    std::cout << "\t." << format_pair.first << std::endl;
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

std::vector<std::string> splitString(const std::string &str,
                                     std::string::value_type delim) {
  std::vector<std::string> result;
  std::istringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delim)) {
    result.push_back(token);
  }

  return result;
}

std::vector<std::string> splitString(const std::string &str) {
  std::istringstream buffer(str);
  std::vector<std::string> result{std::istream_iterator<std::string>(buffer),
                                  std::istream_iterator<std::string>()};
  return result;
}

bool startsWith(const std::string &str, const char *start) {
  return str.rfind(start, 0) == 0;
}

double calculateMeshSurfaceArea(const MeshData &mesh) {
  double surface_area = 0.0;
  for (const auto &triangle : mesh.m_triangles) {
    surface_area += triangle.getArea();
  }
  return surface_area;
}

double calculateMeshVolume(const MeshData &mesh) {
  double volume = 0.0;
  for (const auto &triangle : mesh.m_triangles) {
    volume +=
        triangle.m_a.m_pos.cross3(triangle.m_b.m_pos).dot(triangle.m_c.m_pos);
  }
  return std::abs(volume / 6.0);
}

bool isPointInsideMesh(const MeshData &mesh, const Eigen::Vector4d &point) {
  std::vector<Eigen::Vector4d> intersections;

  for (const auto &triangle : mesh.m_triangles) {

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
  const auto &a = triangle.m_a.m_pos;
  const auto &b = triangle.m_b.m_pos;
  const auto &c = triangle.m_c.m_pos;
  const auto &triangle_normal = triangle.getNormal();

  const double d = triangle_normal.dot(a);
  const double det = triangle_normal.dot(ray_direction);

  if (isEqual(det, 0.0)) {
    return {};
  }

  const double t = (d - triangle_normal.dot(ray_starting_point)) / det;

  if (t < 0) {
    return {};
  }

  const auto &intersection_point = ray_starting_point + t * ray_direction;

  if (isInsideTriangle(intersection_point, triangle))
    return {intersection_point};
  return {};
}

bool isInsideTriangle(const Eigen::Vector4d &point, const Triangle &triangle) {
  const auto &a = triangle.m_a.m_pos;
  const auto &b = triangle.m_b.m_pos;
  const auto &c = triangle.m_c.m_pos;
  const auto &triangle_normal = triangle.getNormal();

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

  for (auto &triangle : mesh.m_triangles) {
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
  transformVector(triangle.m_a.m_pos, transform_matrix);
  transformVector(triangle.m_b.m_pos, transform_matrix);
  transformVector(triangle.m_c.m_pos, transform_matrix);

  transformVector(triangle.m_a.m_normal, transform_matrix_for_normal);
  transformVector(triangle.m_b.m_normal, transform_matrix_for_normal);
  transformVector(triangle.m_c.m_normal, transform_matrix_for_normal);
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