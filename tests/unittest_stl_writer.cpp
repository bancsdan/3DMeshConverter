#include <cstdint>
#include <sstream>

#include "geometry/meshdata.hpp"
#include "writer/stl_writer.hpp"
#include "gtest/gtest.h"

using namespace Converter;

class StlWriterTests : public ::testing::Test, public StlWriter {};

TEST_F(StlWriterTests, TestWriteHeader) {
  std::ostringstream oss;
  EXPECT_EQ(oss.str().size(), 0U);
  writeHeader(oss);
  EXPECT_EQ(oss.str().size(), 80U);
}

TEST_F(StlWriterTests, TestWriteNumOfTriangles) {
  std::ostringstream oss;
  MeshData mesh;
  mesh.triangles.push_back({});
  mesh.triangles.push_back({});
  mesh.triangles.push_back({});
  mesh.triangles.push_back({});
  mesh.triangles.push_back({});
  EXPECT_EQ(oss.str().size(), 0U);

  writeNumOfTriangles(oss, mesh);
  const std::string num_of_triangles_str = oss.str();
  EXPECT_EQ(num_of_triangles_str.size(), 4U);

  const std::uint32_t *const number_of_triangles =
      (std::uint32_t *)num_of_triangles_str.c_str();
  EXPECT_EQ(*number_of_triangles, 5U);
}

TEST_F(StlWriterTests, TestWriteTriangles) {
  Eigen::Vector4d a{-1.0, 0.0, 1.0, 1.0};
  Eigen::Vector4d b{1.0, 0.0, 1.0, 1.0};
  Eigen::Vector4d c{1.0, 0.0, -1.0, 1.0};

  Triangle triangle{a, b, c};
  triangle.a.normal = {0.0, 1.0, 0.0, 0.0};

  MeshData mesh;
  mesh.triangles.push_back(triangle);
  mesh.triangles.push_back(triangle);

  std::ostringstream oss;
  EXPECT_EQ(oss.str().size(), 0U);
  writeTriangles(oss, mesh);
  EXPECT_EQ(oss.str().size(), 100U);

  const std::string current_data_str = oss.str();
  const float *const current_data = (float *)current_data_str.c_str();
  EXPECT_FLOAT_EQ(*current_data, 0.0);

  // read the normal
  EXPECT_FLOAT_EQ(*(current_data + 1), 0.0);
  EXPECT_FLOAT_EQ(*(current_data + 2), 1.0);
  EXPECT_FLOAT_EQ(*(current_data + 3), 0.0);

  // read m_a vertex
  EXPECT_FLOAT_EQ(*(current_data + 4), -1.0);
  EXPECT_FLOAT_EQ(*(current_data + 5), 0.0);
  EXPECT_FLOAT_EQ(*(current_data + 6), 1.0);
  EXPECT_FLOAT_EQ(*(current_data + 7), 1.0);

  // read m_b vertex
  EXPECT_FLOAT_EQ(*(current_data + 8), 1.0);
  EXPECT_FLOAT_EQ(*(current_data + 9), 0.0);
  EXPECT_FLOAT_EQ(*(current_data + 10), 1.0);
  EXPECT_FLOAT_EQ(*(current_data + 11), 1.0);

  // read m_c vertex
  EXPECT_FLOAT_EQ(*(current_data + 12), 1.0);
  EXPECT_FLOAT_EQ(*(current_data + 13), 0.0);
  EXPECT_FLOAT_EQ(*(current_data + 14), -1.0);
  EXPECT_FLOAT_EQ(*(current_data + 15), 1.0);

  // read number of attributes
  EXPECT_FLOAT_EQ(*((std::uint16_t *)current_data + 16), 0U);
}