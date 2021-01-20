#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <Eigen/Dense>
#include <optional>

#include "vertexdata.hpp"

namespace Converter {

/**
 * @brief Data structure for holding vertex data for a single Triangle.
 * @note The members a, b, c are considered to bethe first, second and third
 *       vertices of the triangle. They are public for easy access.
 */
class Triangle {
public:
  VertexData a;
  VertexData b;
  VertexData c;

  /**
   * @brief Default constructor.
   */
  Triangle() = default;

  /**
   * @brief Constructs a Triangle from three VertexData objects defining the
   * vertices.
   * @param a The VertexData for the first vertex.
   * @param b The VertexData for the second vertex.
   * @param c The VertexData for the third vertex.
   */
  Triangle(const VertexData &a, const VertexData &b, const VertexData &c);

  /**
   * @brief Returns the area of the Triangle.
   * @return The area of the Triangle.
   */
  double getArea() const;

  /**
   * @brief Returns the normalized normal vector of the Triangle.
   * @note The returned normal vector is calculated from the vertices of
   * the Triangle, because it can vary between separate vertices based on 
   * the values read from a file.
   * @return The normal vector of the Triangle.
   */
  Eigen::Vector4d getNormal() const;

  /**
   * @brief Returns if two Triangles are equal.
   * @details Compares all the member vertices of the triangle,
   * including vertex positions, normals and textures.
   * @param other The Triangle that this should be compared to.
   * @return True if the two Triangles are equal, otherwise false.
   */
  bool operator==(const Triangle &other) const;

  /**
   * @brief Returns if a Point is in the Triangle.
   * @details It considers points on the edges and vertices to be inside.
   * @param point The point to check.
   * @return True if the point is inside, otherwise false.
   */
  bool isInside(const Eigen::Vector4d &point) const;

  /**
   * @brief Returns the intersection of a ray and the Triangle.
   * @details It considers points on the edges and vertices to be inside.
   * @param ray_starting_point The point in which the ray starts.
   * @param ray_direction The direction of the ray, should be normalized.
   * @return True if the point is inside, otherwise false.
   */
  std::optional<Eigen::Vector4d>
  rayIntersection(const Eigen::Vector4d &ray_starting_point,
                  const Eigen::Vector4d &ray_direction) const;

  /**
   * @brief Transforms the Triangle based on the passed matrices.
   * @param transform_matrix The transformation matrix that should be applied to
   * the vertices.
   * @param transform_matrix_for_normal The transformation matrix for the normal
   * vectors of the matrix.
   */
  void transform(const Eigen::Matrix4d &transform_matrix,
                 const Eigen::Matrix4d &transform_matrix_for_normal);
};

} // namespace Converter

#endif