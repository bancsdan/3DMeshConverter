#ifndef IREADER_HPP
#define IREADER_HPP

#include <string>

namespace Converter {

struct MeshData;

class IReader {
public:
  virtual ~IReader() = default;
  virtual MeshData read(const std::string &file_name) = 0;
};

} // namespace Converter

#endif