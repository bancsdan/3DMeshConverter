#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <Eigen/Dense>
#include <string>
#include <vector>

#include "triangle.hpp"

namespace Converter {

/**
 * @brief Data structure for holding vertex data for a whole 3D mesh object.
 */
class MeshData {
public:
  /**
   * @brief Holds the name of the material file if there is one.
   */
  std::string material_file;
  /**
   * @brief Holds the triangles that the mesh contains.
   */
  std::vector<Triangle> triangles;

  /**
   * @brief Calculates the surface area of the mesh.
   * @return The surface area of the mesh.
   */
  double calculateSurfaceArea() const;

  /**
   * @brief Calculates the volume of the mesh.
   * @return The volume of the mesh.
   */
  double calculateVolume() const;

  /**
   * @brief Determines if a point is inside the mesh or not.
   * @param point The point you wish to know if it's inside.
   * @details The concept of the algorithm is, if the point is inside
   * the mesh and we shoot a ray into any direction, then the number of
   * hit triangles must be odd. The corner case if you hit an edge or vertex,
   * but the implementation handles that.
   * @return True if the point is inside the mesh, otherwise false.
   */
  bool isPointInside(const Eigen::Vector4d &point) const;

  /**
   * @brief Transforms the whole mesh.
   * @param translation_matrix The transformation matrix describing the
   * translation.
   * @param rotation_matrix The transformation matrix describing the
   * rotation.
   * @param scale_matrix The transformation matrix describing the
   * scaling.
   * @details The implementation is using homogeneous coordinates so it
   * can do calculations fast, so these matrices are 4x4.
   * @return True if the point is inside the mesh, otherwise false.
   */
  void transform(const Eigen::Matrix4d &translation_matrix,
                 const Eigen::Matrix4d &rotation_matrix,
                 const Eigen::Matrix4d &scale_matrix);
};

} // namespace Converter

#endif