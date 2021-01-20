#ifndef IREADER_HPP
#define IREADER_HPP

#include <fstream>
#include <string>

namespace Converter {

class MeshData;

/**
 * @brief Interface for classes that read 3D meshes from streams.
 */
class IReader {
public:
  /**
   * @brief Default constructor.
   */
  virtual ~IReader() = default;
  /**
   * @brief Reads data from a file stream and returns it as a MeshData.
   * @param in_file_stream The stream the class should read from.
   * @return The complete mesh in a MeshData object.
   */
  virtual MeshData read(std::istream &in_file_stream) = 0;
};

} // namespace Converter

#endif