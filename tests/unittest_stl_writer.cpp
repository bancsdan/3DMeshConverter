#include <cstdint>
#include <sstream>

#include "geometry/meshdata.hpp"
#include "writer/stl_writer.hpp"
#include "gtest/gtest.h"

using namespace Converter;

// Created to be able to test protected functions
class StlWriterTests : public ::testing::Test, public StlWriter {};

TEST_F(StlWriterTests, TestWriteHeader) {
  std::ostringstream oss;
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

  writeNumOfTriangles(oss, mesh);
  const std::string num_of_triangles_str = oss.str();
  EXPECT_EQ(num_of_triangles_str.size(), 4U);

  const std::uint32_t *const number_of_triangles =
      (std::uint32_t *)num_of_triangles_str.c_str();
  EXPECT_EQ(*number_of_triangles, 5U);
}

TEST_F(StlWriterTests, TestWriteTriangles) {
  Eigen::Vector4d a{-13.26506, 2.2106, 123.550, -421.2206};
  Eigen::Vector4d b{1.00923, 230.230, 11.57082, 1773.6043};
  Eigen::Vector4d c{1.98320, 62.3406343, -1.09430, 3241.0};

  Triangle triangle{a, b, c};
  triangle.a.normal = triangle.getNormal();

  MeshData mesh;
  mesh.triangles.push_back(triangle);
  mesh.triangles.push_back(triangle);

  std::ostringstream oss;
  writeTriangles(oss, mesh);
  EXPECT_EQ(oss.str().size(), 100U);

  const std::string current_data_str = oss.str();
  const float *const current_data = (float *)current_data_str.c_str();

  // read the normal
  EXPECT_FLOAT_EQ(current_data[0], (float)triangle.a.normal.x());
  EXPECT_FLOAT_EQ(current_data[1], (float)triangle.a.normal.y());
  EXPECT_FLOAT_EQ(current_data[2], (float)triangle.a.normal.z());

  // read a vertex
  EXPECT_FLOAT_EQ(current_data[3], (float)triangle.a.pos.x());
  EXPECT_FLOAT_EQ(current_data[4], (float)triangle.a.pos.y());
  EXPECT_FLOAT_EQ(current_data[5], (float)triangle.a.pos.z());

  // read b vertex
  EXPECT_FLOAT_EQ(current_data[6], (float)triangle.b.pos.x());
  EXPECT_FLOAT_EQ(current_data[7], (float)triangle.b.pos.y());
  EXPECT_FLOAT_EQ(current_data[8], (float)triangle.b.pos.z());

  // read c vertex
  EXPECT_FLOAT_EQ(current_data[9], (float)triangle.c.pos.x());
  EXPECT_FLOAT_EQ(current_data[10], (float)triangle.c.pos.y());
  EXPECT_FLOAT_EQ(current_data[11], (float)triangle.c.pos.z());

  // read number of attributes
  EXPECT_EQ(*((std::uint16_t *)(current_data + 12)), 0U);
}