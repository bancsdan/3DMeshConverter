#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <Eigen/Dense>
#include <fstream>
#include <string>
#include <vector>

#include "ireader.hpp"

struct MeshData;

class ObjReader final : public IReader {
  static constexpr char* c_f = "f";
  static constexpr char* c_v = "v";
  static constexpr char* c_vn = "vn";
  static constexpr char* c_vt = "vt";
  static constexpr char* c_mtllib = "mtllib";

  void readFace(const std::vector<std::string>& line,
                const std::vector<Eigen::Vector4d>& vertices,
                const std::vector<Eigen::Vector4d>& vertex_textures,
                const std::vector<Eigen::Vector4d>& vertex_normals,
                MeshData& mesh) const;
  void readVector(const std::vector<std::string>& line,
                  std::vector<Eigen::Vector4d>& vectors) const;

 public:
  MeshData read(const std::string& in_file) final override;
};

#endif