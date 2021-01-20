#include <Eigen/Dense>
#include <algorithm>
#include <array>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "exception.hpp"
#include "geometry/meshdata.hpp"
#include "obj_reader.hpp"
#include "utility.hpp"

namespace Converter {

MeshData ObjReader::read(std::istream &in_file_stream) {
  MeshData result;
  std::vector<Eigen::Vector4d> vertices;
  std::vector<Eigen::Vector4d> vertex_normals;
  std::vector<Eigen::Vector4d> vertex_textures;

  for (std::string line; std::getline(in_file_stream, line);) {
    auto words_vect = Utility::splitString(line);

    if (!words_vect.empty()) {
      if (Utility::startsWith(words_vect[0U], c_vn)) {
        readVector(words_vect, vertex_normals, true);
      } else if (Utility::startsWith(words_vect[0U], c_vt)) {
        readVector(words_vect, vertex_textures);
      } else if (Utility::startsWith(words_vect[0U], c_v)) {
        readVector(words_vect, vertices);
      } else if (Utility::startsWith(words_vect[0U], c_f)) {
        readFace(words_vect, vertices, vertex_textures, vertex_normals, result);
      } else if (Utility::startsWith(words_vect[0U], c_mtllib)) {
        if (words_vect.size() > 1) {
          result.material_file = words_vect[1U];
        }
      }
    }
  }

  return result;
}

void ObjReader::readVector(const std::vector<std::string> &line,
                           std::vector<Eigen::Vector4d> &vectors,
                           bool is_normal) const {
  if (line.size() != 4 && line.size() != 5) {
    throw IllFormedFileException();
  }

  Eigen::Vector4d vec{0.0, 0.0, 0.0, is_normal ? 0.0 : 1.0};
  unsigned int index = 0U;
  for (auto it = line.begin() + 1; it != line.end(); ++it) {
    try {
      vec[index++] = std::stod(*it);
    } catch (const std::exception &) {
      throw IllFormedFileException();
    }
  }

  vectors.push_back(vec);
}

std::array<std::optional<int>, 3U>
ObjReader::readIndicesFromSlashSeparatedWord(const std::string &word) const {
  std::array<std::optional<int>, 3U> result;
  std::istringstream iss(word);

  for (auto &elem : result) {
    std::string idx;
    std::getline(iss, idx, '/');
    if (!idx.empty()) {
      elem = std::stoi(idx);
    }
  }

  return result;
}

void ObjReader::readFace(const std::vector<std::string> &line,
                         const std::vector<Eigen::Vector4d> &vertices,
                         const std::vector<Eigen::Vector4d> &vertex_textures,
                         const std::vector<Eigen::Vector4d> &vertex_normals,
                         MeshData &mesh) const {
  if (line.size() < 4U) {
    throw IllFormedFileException();
  }

  std::vector<const Eigen::Vector4d *> face_vertices;
  std::vector<const Eigen::Vector4d *> face_vertex_textures;
  std::vector<const Eigen::Vector4d *> face_vertex_normals;
  for (auto it = line.begin() + 1U; it != line.end(); ++it) {
    try {
      const auto face_vertex_indices = readIndicesFromSlashSeparatedWord(*it);
      face_vertices.push_back(&vertices[face_vertex_indices[0U].value() - 1U]);
      if (face_vertex_indices[1U]) {
        face_vertex_textures.push_back(
            &vertex_textures[face_vertex_indices[1U].value() - 1U]);
      }
      if (face_vertex_indices[2U]) {
        face_vertex_normals.push_back(
            &vertex_normals[face_vertex_indices[2U].value() - 1U]);
      }
    } catch (const std::exception &) {
      throw IllFormedFileException();
    }
  }

  if (face_vertex_textures.size() != 0U &&
      face_vertex_textures.size() != face_vertices.size()) {
    throw IllFormedFileException();
  }
  if (face_vertex_normals.size() != 0U &&
      face_vertex_normals.size() != face_vertices.size()) {
    throw IllFormedFileException();
  }

  for (std::size_t i = 0U; i < face_vertices.size() - 2U; ++i) {
    Triangle triangle;

    triangle.a.pos = *face_vertices[0U];
    triangle.b.pos = *face_vertices[i + 1U];
    triangle.c.pos = *face_vertices[i + 2U];

    if (face_vertex_textures.size() != 0U) {
      triangle.a.texture = *face_vertex_textures[0U];
      triangle.b.texture = *face_vertex_textures[i + 1U];
      triangle.c.texture = *face_vertex_textures[i + 2U];
    }

    if (face_vertex_normals.size() != 0U) {
      triangle.a.normal = *face_vertex_normals[0U];
      triangle.b.normal = *face_vertex_normals[i + 1U];
      triangle.c.normal = *face_vertex_normals[i + 2U];
    }

    mesh.triangles.push_back(std::move(triangle));
  }
}

} // namespace Converter