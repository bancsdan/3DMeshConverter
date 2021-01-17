#ifndef STL_WRITER_HPP
#define STL_WRITER_HPP

#include <string>

#include "iwriter.hpp"

namespace Converter {

struct MeshData;

class StlWriter final : public IWriter {
private:
  static constexpr unsigned int c_header_size_in_bytes = 80U;

  void writeHeader(std::ofstream &out_file) const;
  void writeNumOfTriangles(std::ofstream &out_file, const MeshData &mesh) const;
  void writeTriangles(std::ofstream &out_file, const MeshData &mesh) const;

public:
  void write(const std::string &file_name,
             const MeshData &mesh) const final override;
};

} // namespace Converter

#endif