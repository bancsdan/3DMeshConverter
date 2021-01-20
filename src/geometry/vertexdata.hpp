#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <Eigen/Dense>
#include <string>

namespace Converter {

struct VertexData {
  Eigen::Vector4d pos{0.0, 0.0, 0.0, 1.0};
  Eigen::Vector4d normal{0.0, 0.0, 0.0, 0.0};
  Eigen::Vector4d texture{0.0, 0.0, 0.0, 0.0};

  VertexData() = default;
  VertexData(const Eigen::Vector4d &pos) : pos(pos) {}
};

} // namespace Converter

#endif