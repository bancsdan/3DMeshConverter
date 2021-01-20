#ifndef IWRITER_HPP
#define IWRITER_HPP

#include <fstream>
#include <string>

namespace Converter {

class MeshData;

class IWriter {
public:
  virtual ~IWriter() = default;
  virtual void write(std::ostream &out_file, const MeshData &mesh) const = 0;
};
} // namespace Converter

#endif