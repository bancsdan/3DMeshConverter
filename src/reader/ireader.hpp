#ifndef IREADER_HPP
#define IREADER_HPP

#include <fstream>
#include <string>

namespace Converter {

class MeshData;

class IReader {
public:
  virtual ~IReader() = default;
  virtual MeshData read(std::istream &in_file_stream) = 0;
};

} // namespace Converter

#endif