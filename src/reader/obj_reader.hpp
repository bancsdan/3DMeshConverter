#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <Eigen/Dense>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <optional>

#include "ireader.hpp"

namespace Converter {

struct MeshData;

class ObjReader : public IReader {
protected:
  static constexpr const char *c_f = "f";
  static constexpr const char *c_v = "v";
  static constexpr const char *c_vn = "vn";
  static constexpr const char *c_vt = "vt";
  static constexpr const char *c_mtllib = "mtllib";
  
  std::array<std::optional<int>, 3U> readIndicesFromSlashSeparatedWord(const std::string& word) const;
  void readFace(const std::vector<std::string> &line,
                const std::vector<Eigen::Vector4d> &vertices,
                const std::vector<Eigen::Vector4d> &vertex_textures,
                const std::vector<Eigen::Vector4d> &vertex_normals,
                MeshData &mesh) const;
  void readVector(const std::vector<std::string> &line,
                  std::vector<Eigen::Vector4d> &vectors, bool is_normal = false) const;

public:
  MeshData read(std::istream& in_file_stream) override;
};

} // namespace Converter

#endif