#ifndef IREADER_HPP
#define IREADER_HPP

#include <string>
#include <fstream>

namespace Converter {

struct MeshData;

class IReader {
public:
  virtual ~IReader() = default;
  virtual MeshData read(std::istream& in_file_stream) = 0;
};

} // namespace Converter

#endif