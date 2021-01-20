#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <Eigen/Dense>
#include <array>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "ireader.hpp"

namespace Converter {

class MeshData;

/**
 * @brief Reader implementation for .obj type of files.
 */
class ObjReader : public IReader {
protected:
  /**
   * @param c_f Represents a face in the .obj file.
   * @param c_v Represents a vertex in the .obj file.
   * @param c_vn Represents a vertex normal in the .obj file.
   * @param c_vt Represents a vertext texture in the .obj file.
   * @param c_mtllib Represents the material file in the .obj file.
   */
  static constexpr const char *c_f = "f";
  static constexpr const char *c_v = "v";
  static constexpr const char *c_vn = "vn";
  static constexpr const char *c_vt = "vt";
  static constexpr const char *c_mtllib = "mtllib";

  /**
   * @brief Reads the indices defined by a face for example, between slashes.
   * @details We have to know if there were actual values present, since .obj
   * format supports optional normals or textures, we return optionals in the
   * return array.
   * @param word The word containing the indices and the slashes we would like
   * to read from.
   * @return An array of optionals of size 3, with the values present that were
   * read from the word.
   */
  std::array<std::optional<int>, 3U>
  readIndicesFromSlashSeparatedWord(const std::string &word) const;

  /**
   * @brief Reads the definition of a face from the .obj file.
   * @details Reads the indices, vertex normals textures from the .obj file,
   * if there are more than 3 indices, it triangulates it.
   * @param line The line from the file that has to be read. It starts with 'f'.
   * @param vertices The already read vertices from the file.
   * @param vertex_textures The already read vertex textures from the file.
   * @param vertex_normals The already read vertex normals from the file.
   * @param mesh The mesh to be populated with the data.
   * @throw IllFormedFileException Any indexing, reading, etc. exceptions imply
   * an ill formed input file, so those are caught and this exception is thrown
   * instead. Also if the read data doesn't conform to the standard, this
   * exception is thrown.
   */
  void readFace(const std::vector<std::string> &line,
                const std::vector<Eigen::Vector4d> &vertices,
                const std::vector<Eigen::Vector4d> &vertex_textures,
                const std::vector<Eigen::Vector4d> &vertex_normals,
                MeshData &mesh) const;

  /**
   * @brief Reads the definition of a vector from the .obj file.
   * @details Multiple types of objects are defined in the same way in .obj
   * files, either with 3 or 4 coordinates. They can all be read with this
   * function. The param is_normal is needed, because of the usage of
   * homogeneous coordinates where the 4th parameter has a default value of 0.0
   * on contrary to points which have 1.0.
   * @param line The line from the file that has to be read.
   * @param vectors The vector that you wish to read vectors into.
   * @param is_normal Signals if the read vector is a normal or not.
   * @throw IllFormedFileException Any indexing, reading, etc. exceptions imply
   * an ill formed input file, so those are caught and this exception is thrown
   * instead.
   */
  void readVector(const std::vector<std::string> &line,
                  std::vector<Eigen::Vector4d> &vectors,
                  bool is_normal = false) const;

public:
  /**
   * @brief Reads the mesh from an .obj file or stream.
   * @param in_stream The stream the function should read from.
   * @return A MeshData object that contains all the data that could be read
   * from the .obj file.
   */
  MeshData read(std::istream &in_stream) override;
};

} // namespace Converter

#endif