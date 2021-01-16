#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <string>
#include <vector>

#include "triangle.hpp"

namespace Converter {

struct MeshData {
  std::string m_material_file;
  std::vector<Triangle> m_triangles;
};

}  // namespace Converter

#endif