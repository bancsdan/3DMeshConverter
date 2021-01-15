#ifndef STL_WRITER_HPP
#define STL_WRITER_HPP

#include <string>

#include "iwriter.hpp"

struct MeshData;

class StlWriter final : public IWriter {
  static constexpr unsigned int c_header_size_in_bytes = 80U;
  static constexpr unsigned int c_triangle_size_in_bytes = 50U;
  static constexpr unsigned int c_max_num_of_triangles_in_buffer = 1024U;
  static constexpr unsigned int c_triangle_buffer_size_in_bytes =
      c_triangle_size_in_bytes * c_max_num_of_triangles_in_buffer;

  void writeHeader(std::ofstream& out_file) const;
  void writeNumOfTriangles(std::ofstream& out_file, const MeshData& mesh) const;
  void writeTriangles(std::ofstream& out_file, const MeshData& mesh) const;

 public:
  void write(const std::string& file_name,
             const MeshData& mesh) const final override;
};

#endif