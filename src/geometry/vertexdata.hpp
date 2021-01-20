#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <Eigen/Dense>
#include <string>

namespace Converter {

/**
 * @brief Data structure for holding related data for a single vertex.
 * @details The coordinates are homogeneous, for fast transformations
 * with matrices and future compatibility.
 */
struct VertexData {
  /**
   * @brief Holds the position of the vertex.
   */
  Eigen::Vector4d pos{0.0, 0.0, 0.0, 1.0};
  /**
   * @brief Holds the normal of the vertex.
   */
  Eigen::Vector4d normal{0.0, 0.0, 0.0, 0.0};
  /**
   * @brief Holds the texture of the vertex.
   */
  Eigen::Vector4d texture{0.0, 0.0, 0.0, 0.0};

  /**
   * @brief Default constructor.
   */
  VertexData() = default;

  /**
   * @brief Parametrized constructor of Vertexdata.
   * @details Allows implicit conversion from an Eigen::Vector4d,
   * assuming it is the position of the created vertex.
   * @param pos The position of the vertex.
   */
  VertexData(const Eigen::Vector4d &pos) : pos(pos) {}
};

} // namespace Converter

#endif