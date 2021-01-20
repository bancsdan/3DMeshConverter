#ifndef IWRITER_HPP
#define IWRITER_HPP

#include <fstream>
#include <string>

namespace Converter {

class MeshData;

/**
 * @brief Interface for classes that write 3D meshes to stream.
 */
class IWriter {
public:
  /**
   * @brief Default constructor.
   */
  virtual ~IWriter() = default;

  /**
   * @brief Writes mesh data to the output stream.
   * @param out_file_stream The stream the class should write data to.
   * @param mesh The mesh the function should write the data from.
   */
  virtual void write(std::ostream &out_file, const MeshData &mesh) const = 0;
};
} // namespace Converter

#endif