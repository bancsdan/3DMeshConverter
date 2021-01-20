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
  mesh.m_triangles.push_back({});
  mesh.m_triangles.push_back({});
  mesh.m_triangles.push_back({});
  mesh.m_triangles.push_back({});
  mesh.m_triangles.push_back({});
  EXPECT_EQ(oss.str().size(), 0U);

  writeNumOfTriangles(oss, mesh);
  const std::string num_of_triangles_str = oss.str();
  EXPECT_EQ(num_of_triangles_str.size(), 4U);

  const std::uint32_t *const number_of_triangles =
      (std::uint32_t *)num_of_triangles_str.c_str();
  EXPECT_EQ(*number_of_triangles, 5U);
}