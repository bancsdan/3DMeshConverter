#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <string>
#include <vector>

#include "triangle.hpp"

namespace Converter {

struct MeshData {
  std::string material_file;
  std::vector<Triangle> triangles;
};

} // namespace Converter

#endif