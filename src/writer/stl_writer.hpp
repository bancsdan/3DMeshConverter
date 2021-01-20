#ifndef STL_WRITER_HPP
#define STL_WRITER_HPP

#include <string>

#include "iwriter.hpp"

namespace Converter {

class MeshData;

/**
 * @brief Writer implementation for .stl type of files.
 */
class StlWriter : public IWriter {
protected:
  /**
   * @brief The standard header size for .stl format.
   */
  static constexpr unsigned int c_header_size_in_bytes = 80U;

  /**
   * @brief Writes header data to the output stream.
   * @note The .stl format generally ignores headers, so currently
   * this function just fills the header with zeroes.
   * @param out_file The stream the header should be written to.
   */
  void writeHeader(std::ostream &out_stream) const;

  /**
   * @brief Writes the number of Triangles in the mesh to the stream.
   * @param out_file The stream the number of Triangles should be written to.
   * @param mesh The mesh containing the Triangles.
   */
  void writeNumOfTriangles(std::ostream &out_stream,
                           const MeshData &mesh) const;

  /**
   * @brief Writes the Triangles in the mesh to the stream.
   * @note Also writes 2 bytes of attribute count data, but it is always zero.
   * @param out_file The stream the Triangles should be written to.
   * @param mesh The mesh containing the Triangles.
   */
  void writeTriangles(std::ostream &out_stream, const MeshData &mesh) const;

public:
  /**
   * @brief Writes the mesh data to the output stream.
   * @param out_stream The stream the mesh data should be written to.
   * @param mesh The mesh data itself.
   */
  void write(std::ostream &out_stream,
             const MeshData &mesh) const final override;
};

} // namespace Converter

#endif