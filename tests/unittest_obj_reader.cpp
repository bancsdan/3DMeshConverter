#include <Eigen/Dense>
#include <array>
#include <exception>
#include <optional>
#include <string>
#include <vector>

#include "exception.hpp"
#include "geometry/meshdata.hpp"
#include "reader/obj_reader.hpp"
#include "gtest/gtest.h"

using namespace Converter;

class ObjReaderTests : public ::testing::Test, public ObjReader {};

TEST_F(ObjReaderTests, TestReadVector) {
  std::vector<std::string> line;
  std::vector<Eigen::Vector4d> read_vectors;
  line.push_back("v");
  EXPECT_THROW(readVector(line, read_vectors), IllFormedFileException);

  line.push_back("2.3");
  line.push_back("4.2");
  line.push_back("-3.4");
  readVector(line, read_vectors);
  EXPECT_TRUE(read_vectors[0U].isApprox(Eigen::Vector4d{2.3, 4.2, -3.4, 1.0}));

  line.push_back("942342.4623523");
  readVector(line, read_vectors);
  EXPECT_TRUE(read_vectors[1U].isApprox(
      Eigen::Vector4d{2.3, 4.2, -3.4, 942342.4623523}));
}

TEST_F(ObjReaderTests, TestReadFace) {
  std::vector<std::string> line;
  std::vector<Eigen::Vector4d> vertices;
  std::vector<Eigen::Vector4d> vertex_textures;
  std::vector<Eigen::Vector4d> vertex_normals;

  Eigen::Vector4d a{1.0, 0.0, 0.0, 1.0};
  Eigen::Vector4d b{2.0, 0.0, 0.0, 1.0};
  Eigen::Vector4d c{2.0, 0.0, -1.0, 1.0};
  Eigen::Vector4d d{1.0, 0.0, -1.0, 1.0};

  Eigen::Vector4d norm{0.0, 1.0, 0.0, 0.0};

  Eigen::Vector4d at{0.0, 0.0, 0.0, 1.0};
  Eigen::Vector4d bt{1.0, 0.0, 0.0, 1.0};
  Eigen::Vector4d ct{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d dt{0.0, 1.0, 0.0, 1.0};

  vertices.push_back(a);
  vertices.push_back(b);
  vertices.push_back(c);
  vertices.push_back(d);

  vertex_normals.push_back({0.0, 1.0, 0.0, 0.0});

  vertex_textures.push_back({0.0, 0.0, 0.0, 1.0});
  vertex_textures.push_back({1.0, 0.0, 0.0, 1.0});
  vertex_textures.push_back({1.0, 1.0, 0.0, 1.0});
  vertex_textures.push_back({0.0, 1.0, 0.0, 1.0});

  Triangle triangle_1{a, b, c};
  triangle_1.m_a.m_normal = norm;
  triangle_1.m_b.m_normal = norm;
  triangle_1.m_c.m_normal = norm;
  triangle_1.m_a.m_texture = at;
  triangle_1.m_b.m_texture = bt;
  triangle_1.m_c.m_texture = ct;

  Triangle triangle_2{a, c, d};
  triangle_2.m_a.m_normal = norm;
  triangle_2.m_b.m_normal = norm;
  triangle_2.m_c.m_normal = norm;
  triangle_2.m_a.m_texture = at;
  triangle_2.m_b.m_texture = ct;
  triangle_2.m_c.m_texture = dt;

  MeshData mesh;
  std::vector<Eigen::Vector4d> read_vectors;
  line.push_back("f");
  line.push_back("//");
  line.push_back("2//");

  EXPECT_THROW(readFace(line, vertices, vertex_textures, vertex_normals, mesh),
               IllFormedFileException);

  line.push_back("3//");
  line.push_back("4//");
  EXPECT_THROW(readFace(line, vertices, vertex_textures, vertex_normals, mesh),
               IllFormedFileException);

  line = {};
  line.push_back("f");
  line.push_back("1/1/1");
  line.push_back("2/2/1");
  line.push_back("3/3/1");
  line.push_back("4/4/1");
  readFace(line, vertices, vertex_textures, vertex_normals, mesh);
  EXPECT_TRUE(mesh.m_triangles[0U] == triangle_1);
  EXPECT_TRUE(mesh.m_triangles[1U] == triangle_2);

  line = {};
  line.push_back("f");
  line.push_back("1//");
  line.push_back("2//");
  line.push_back("3//");
  line.push_back("4//");
  readFace(line, vertices, vertex_textures, vertex_normals, mesh);
  EXPECT_TRUE(mesh.m_triangles[2U].m_a.m_pos.isApprox(triangle_1.m_a.m_pos));
  EXPECT_TRUE(mesh.m_triangles[2U].m_b.m_pos.isApprox(triangle_1.m_b.m_pos));
  EXPECT_TRUE(mesh.m_triangles[2U].m_c.m_pos.isApprox(triangle_1.m_c.m_pos));
  EXPECT_TRUE(mesh.m_triangles[3U].m_a.m_pos.isApprox(triangle_2.m_a.m_pos));
  EXPECT_TRUE(mesh.m_triangles[3U].m_b.m_pos.isApprox(triangle_2.m_b.m_pos));
  EXPECT_TRUE(mesh.m_triangles[3U].m_c.m_pos.isApprox(triangle_2.m_c.m_pos));
  EXPECT_FALSE(
      mesh.m_triangles[2U].m_a.m_normal.isApprox(triangle_1.m_a.m_normal));
  EXPECT_FALSE(
      mesh.m_triangles[2U].m_b.m_normal.isApprox(triangle_1.m_b.m_normal));
  EXPECT_FALSE(
      mesh.m_triangles[2U].m_c.m_normal.isApprox(triangle_1.m_c.m_normal));
  EXPECT_FALSE(
      mesh.m_triangles[3U].m_a.m_normal.isApprox(triangle_2.m_a.m_normal));
  EXPECT_FALSE(
      mesh.m_triangles[3U].m_b.m_normal.isApprox(triangle_2.m_b.m_normal));
  EXPECT_FALSE(
      mesh.m_triangles[3U].m_c.m_normal.isApprox(triangle_2.m_c.m_normal));
}

TEST_F(ObjReaderTests, TestReadIndicesFromSlashSeparatedWord) {
  std::array<std::optional<int>, 3U> result =
      readIndicesFromSlashSeparatedWord("//");
  EXPECT_FALSE(result[0U]);
  EXPECT_FALSE(result[1U]);
  EXPECT_FALSE(result[2U]);

  result = readIndicesFromSlashSeparatedWord("1//");
  EXPECT_EQ(result[0U].value(), 1);
  EXPECT_FALSE(result[1U]);
  EXPECT_FALSE(result[2U]);

  result = readIndicesFromSlashSeparatedWord("1//5");
  EXPECT_EQ(result[0U], 1);
  EXPECT_FALSE(result[1U]);
  EXPECT_EQ(result[2U], 5);

  result = readIndicesFromSlashSeparatedWord("1/9/5");
  EXPECT_EQ(result[0U], 1);
  EXPECT_EQ(result[1U], 9);
  EXPECT_EQ(result[2U], 5);
}

TEST_F(ObjReaderTests, TestRead) {
  std::ifstream in_file_stream;
  in_file_stream.open("test_file.obj");
  EXPECT_TRUE(in_file_stream);

  MeshData mesh = read(in_file_stream);

  Eigen::Vector4d a{-1.3143, 15.0686, -1.6458, 1.0};
  Eigen::Vector4d b{-1.4575, 15.1137, -1.5916, 1.0};
  Eigen::Vector4d c{-1.3688, 15.2156, -1.6669, 1.0};
  Eigen::Vector4d an{-0.3819, -0.2594, -0.8871, 0.0};
  Eigen::Vector4d bn{-0.4376, -0.2949, -0.8495, 0.0};
  Eigen::Vector4d cn{-0.3783, -0.2771, -0.8832, 0.0};
  Eigen::Vector4d at{1.0, 0.0, 0.0, 1.0};
  Eigen::Vector4d bt{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d ct{0.0, 1.0, 1.0, 1.0};

  Triangle triangle{a, b, c};
  triangle.m_a.m_normal = an;
  triangle.m_b.m_normal = bn;
  triangle.m_c.m_normal = cn;
  triangle.m_a.m_texture = at;
  triangle.m_b.m_texture = bt;
  triangle.m_c.m_texture = ct;

  EXPECT_TRUE(mesh.m_triangles[0U] == triangle);
}