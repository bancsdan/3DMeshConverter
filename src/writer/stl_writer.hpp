#ifndef STL_WRITER_HPP
#define STL_WRITER_HPP

#include <string>

#include "iwriter.hpp"

namespace Converter {

struct MeshData;

class StlWriter : public IWriter {
protected:
  static constexpr unsigned int c_header_size_in_bytes = 80U;

  void writeHeader(std::ostream &out_file) const;
  void writeNumOfTriangles(std::ostream &out_file, const MeshData &mesh) const;
  void writeTriangles(std::ostream &out_file, const MeshData &mesh) const;

public:
  void write(std::ostream &out_file, const MeshData &mesh) const final override;
};

} // namespace Converter

#endif