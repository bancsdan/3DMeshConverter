#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <Eigen/Dense>
#include <string>
#include <vector>

#include "triangle.hpp"

namespace Converter {

class MeshData {
public:
  std::string material_file;
  std::vector<Triangle> triangles;

  double calculateSurfaceArea() const;
  double calculateVolume() const;
  bool isPointInside(const Eigen::Vector4d &point) const;
  void transform(const Eigen::Matrix4d &translation_matrix,
                 const Eigen::Matrix4d &rotation_matrix,
                 const Eigen::Matrix4d &scale_matrix);
};

} // namespace Converter

#endif