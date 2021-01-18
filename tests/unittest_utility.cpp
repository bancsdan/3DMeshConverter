#include <Eigen/Dense>
#include <cstdint>
#include <string>

#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "utility.hpp"
#include "gtest/gtest.h"

using namespace Converter;

namespace {

static constexpr double PI = 3.141592653589793238;
static constexpr double EPSILON = 0.0000001;

static MeshData getCube() {
  Eigen::Vector4d a{-1.0, -1.0, 1.0, 1.0};
  Eigen::Vector4d b{1.0, -1.0, 1.0, 1.0};
  Eigen::Vector4d c{1.0, 1.0, 1.0, 1.0};
  Eigen::Vector4d d{-1.0, 1.0, 1.0, 1.0};
  Eigen::Vector4d e{1.0, -1.0, -1.0, 1.0};
  Eigen::Vector4d f{-1.0, -1.0, -1.0, 1.0};
  Eigen::Vector4d g{-1.0, 1.0, -1.0, 1.0};
  Eigen::Vector4d h{1.0, 1.0, -1.0, 1.0};

  MeshData mesh;
  mesh.m_triangles.push_back({a, b, c});
  mesh.m_triangles.push_back({a, c, d});
  mesh.m_triangles.push_back({b, e, h});
  mesh.m_triangles.push_back({b, h, c});
  mesh.m_triangles.push_back({e, f, g});
  mesh.m_triangles.push_back({e, g, h});
  mesh.m_triangles.push_back({f, a, d});
  mesh.m_triangles.push_back({f, d, g});
  mesh.m_triangles.push_back({d, c, h});
  mesh.m_triangles.push_back({d, h, g});
  mesh.m_triangles.push_back({f, e, b});
  mesh.m_triangles.push_back({f, b, a});

  return mesh;
}

static MeshData getDoublePyramid() {
  Eigen::Vector4d a{-1.0, 0.0, 1.0, 1.0};
  Eigen::Vector4d b{1.0, 0.0, 1.0, 1.0};
  Eigen::Vector4d c{1.0, 0.0, -1.0, 1.0};
  Eigen::Vector4d d{-1.0, 0.0, -1.0, 1.0};
  Eigen::Vector4d p{0.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d q{0.0, -1.0, 0.0, 1.0};

  MeshData mesh;
  mesh.m_triangles.push_back({a, b, p});
  mesh.m_triangles.push_back({b, c, p});
  mesh.m_triangles.push_back({c, d, p});
  mesh.m_triangles.push_back({d, a, p});
  mesh.m_triangles.push_back({a, q, b});
  mesh.m_triangles.push_back({b, q, c});
  mesh.m_triangles.push_back({c, q, d});
  mesh.m_triangles.push_back({d, q, a});

  return mesh;
}

} // namespace

TEST(UtilityTests, TestToLower) {
  std::string str{"ABCdef123$!"};
  EXPECT_EQ(Utility::toLower(str), "abcdef123$!");

  str = "";
  EXPECT_EQ(Utility::toLower(str), "");
}

TEST(UtilityTests, TestSplitString) {
  std::vector<std::string> expected_result;
  expected_result.push_back("Abc");
  expected_result.push_back("def");
  expected_result.push_back("ghi!");

  auto result = Utility::splitString("Abc def ghi!");
  EXPECT_EQ(result, expected_result);

  result = Utility::splitString("Abc def  ghi!");
  EXPECT_EQ(result, expected_result);

  result = Utility::splitString("Abc/def/ghi!/", '/');
  EXPECT_EQ(result, expected_result);

  expected_result.insert(expected_result.begin() + 2, "");
  result = Utility::splitString("Abc/def//ghi!", '/');
  EXPECT_EQ(result, expected_result);

  expected_result = {};
  expected_result.push_back("Abc");
  result = Utility::splitString("Abc");
  EXPECT_EQ(result, expected_result);

  result = Utility::splitString("Abc", '/');
  EXPECT_EQ(result, expected_result);
}

TEST(UtilityTests, TestStartsWith) {
  std::string str{"Abc!de"};

  EXPECT_TRUE(Utility::startsWith(str, "A"));
  EXPECT_TRUE(Utility::startsWith(str, "Abc!"));
  EXPECT_TRUE(Utility::startsWith(str, "Abc!de"));
  EXPECT_FALSE(Utility::startsWith(str, "Abc!def"));
  EXPECT_FALSE(Utility::startsWith(str, "bc"));
}

TEST(UtilityTests, TestCalculateMeshSurfaceArea) {
  MeshData mesh = getCube();
  EXPECT_DOUBLE_EQ(Utility::calculateMeshSurfaceArea(mesh), 24.0);

  mesh = getDoublePyramid();
  EXPECT_DOUBLE_EQ(Utility::calculateMeshSurfaceArea(mesh), 11.31370849898476);
}

TEST(UtilityTests, TestCalculateMeshVolume) {
  MeshData mesh = getDoublePyramid();
  EXPECT_DOUBLE_EQ(Utility::calculateMeshVolume(mesh), 8.0 / 3.0);

  mesh = getCube();
  EXPECT_DOUBLE_EQ(Utility::calculateMeshVolume(mesh), 8.0);
}

TEST(UtilityTests, TestIsPointInsideMesh) {
  MeshData mesh = getDoublePyramid();

  Eigen::Vector4d testp{0.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -2.0, 0.0, 1.0};
  EXPECT_FALSE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -1.0, 0.0, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -1.00001, 0.0, 1.0};
  EXPECT_FALSE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -0.99999, 0.0, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {1.0, 0.0, 1.0, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {1.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, 1.0, 0.0, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {1.00001, 0.0, 0.0, 1.0};
  EXPECT_FALSE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.29684, -0.234, 0.194, 1.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));
}

TEST(UtilityTests, TestRayTriangleIntersection) {
  Eigen::Vector4d a{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d b{-1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d c{0.0, 1.0, 1.0, 1.0};
  Triangle triangle{a, b, c};

  Eigen::Vector4d ray_start_point{0.0, 0.0, 0.5, 1.0};
  Eigen::Vector4d ray_dir{0.0, -1.0, 0.0, 0.0};
  auto hit =
      Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_FALSE(hit);

  ray_start_point = {0.0, 0.0, 0.5, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(Eigen::Vector4d{0.0, 1.0, 0.5, 1.0}));

  ray_start_point = {1.0, 0.0, 0.0, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(a));

  ray_start_point = {1.001, 0.0, 0.0, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_FALSE(hit);

  ray_start_point = {0.0, 1.0, 0.5, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(ray_start_point));

  ray_start_point = {0.2, 0.1, 0.4, 1.0};
  ray_dir = {-0.3, 0.8, -0.2, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(Eigen::Vector4d{-0.1375, 1.0, 0.175, 1.0}));
}

TEST(UtilityTests, TestIsInsideTriangle) {
  Eigen::Vector4d a{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d b{-1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d c{0.0, 1.0, 1.0, 1.0};
  Triangle triangle{a, b, c};

  EXPECT_TRUE(Utility::isInsideTriangle(a, triangle));
  EXPECT_TRUE(Utility::isInsideTriangle(b, triangle));
  EXPECT_TRUE(Utility::isInsideTriangle(c, triangle));

  Eigen::Vector4d a_moved{1.0001, 1.0, 0.0, 1.0};
  EXPECT_FALSE(Utility::isInsideTriangle(a_moved, triangle));
  Eigen::Vector4d b_moved{-1.0001, 1.0, 0.0, 1.0};
  EXPECT_FALSE(Utility::isInsideTriangle(b_moved, triangle));
  Eigen::Vector4d c_moved{0, 1.0, 1.1, 1.0};
  EXPECT_FALSE(Utility::isInsideTriangle(c_moved, triangle));

  Eigen::Vector4d d{0, 1.0, 0.5, 1.0};
  EXPECT_TRUE(Utility::isInsideTriangle(d, triangle));
  Eigen::Vector4d d_moved = {0, 1.1, 0.5, 1.0};
  EXPECT_FALSE(Utility::isInsideTriangle(d_moved, triangle));

  a = {0.0, 1.0, 0.0, 1.0};
  b = {1.0, 0.0, 0.0, 1.0};
  c = {1.0, 0.0, -11.0, 1.0};
  triangle = {a, b, c};
  EXPECT_FALSE(Utility::isInsideTriangle({0.5, 0.5001, -0.1, 1.0}, triangle));
  EXPECT_TRUE(Utility::isInsideTriangle({0.5, 0.5, -0.1, 1.0}, triangle));
}

TEST(UtilityTests, TestTransformVector) {
  Eigen::Vector4d point;

  // pure rotations
  point = {1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d rotation_matrix =
      Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{0.0, 0.0, -1.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{1.0, 0.0, 0.0, 1.0}));

  point = {1.0, 0.0, 0.0, 1.0};
  rotation_matrix = Utility::getRotationMatrix({0.0, 0.0, 1.0}, PI);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = Utility::getRotationMatrix({1.0, 0.0, 0.0}, PI);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = Utility::getRotationMatrix({8.213, -5.231, 1.894}, 0.0);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix =
      Utility::getRotationMatrix({8.213, -5.231, 1.894}, PI / 5.0);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(
      Eigen::Vector4d{-0.939931, -0.0288444, -0.340144, 1.0}, EPSILON));

  // pure translations
  point = {-1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d translation_matrix =
      Utility::getTranslationMatrix({0.0, 0.0, 0.0});
  Utility::transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 1.0, 0.0, 1.0};
  translation_matrix = Utility::getTranslationMatrix({1.0, -1.0, 0.0});
  Utility::transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{0.0, 0.0, 0.0, 1.0}));

  point = {0.0, 0.0, 0.0, 1.0};
  translation_matrix = Utility::getTranslationMatrix({3.9123, -5.123, 11.0092});
  Utility::transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{3.9123, -5.123, 11.0092, 1.0}));

  // pure scaling
  point = {-1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d scale_matrix = Utility::getScaleMatrix({1.0, 1.0, 1.0});
  Utility::transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  scale_matrix = Utility::getScaleMatrix({0.5, 0.5, 0.5});
  Utility::transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-0.5, 0.0, 0.0, 1.0}));

  point = {1.0, 1.0, 1.0, 1.0};
  scale_matrix = Utility::getScaleMatrix({5.92, -12.0, 3.08});
  Utility::transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{5.92, -12.0, 3.08, 1.0}));

  // combined
  point = {1.0, 0.0, 0.0, 1.0};
  scale_matrix = Utility::getScaleMatrix({2.0, 1.0, 1.0});
  rotation_matrix = Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  translation_matrix = Utility::getTranslationMatrix({1.0, -1.0, 0.0});

  const Eigen::Matrix4d &transformation_matrix =
      translation_matrix * rotation_matrix * scale_matrix;

  Utility::transformVector(point, transformation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{1.0, -1.0, -2.0, 1.0}));
}

TEST(UtilityTests, TestTransformTriangle) {
  Eigen::Vector4d a{1.0, 0.0, 1.0, 1.0};
  Eigen::Vector4d b{1.0, 0.0, -1.0, 1.0};
  Eigen::Vector4d c{1.0, 2.0, 0.0, 1.0};

  Triangle original_triangle{a, b, c};
  original_triangle.m_a.m_normal = original_triangle.getNormal();
  original_triangle.m_b.m_normal = original_triangle.getNormal();
  original_triangle.m_c.m_normal = original_triangle.getNormal();

  Triangle test_triangle = original_triangle;
  auto rotation_matrix = Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  auto normal_rotation_matrix = rotation_matrix.inverse().transpose();
  Utility::transformTriangle(test_triangle, rotation_matrix,
                             normal_rotation_matrix);

  EXPECT_TRUE(
      test_triangle.m_a.m_pos.isApprox(Eigen::Vector4d{1.0, 0.0, -1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.m_b.m_pos.isApprox(Eigen::Vector4d{-1.0, 0.0, -1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.m_c.m_pos.isApprox(Eigen::Vector4d{0.0, 2.0, -1.0, 1.0}));

  EXPECT_TRUE(test_triangle.m_a.m_normal.isApprox(
      Eigen::Vector4d{0.0, 0.0, -1.0, 0.0}));
  EXPECT_TRUE(test_triangle.m_b.m_normal.isApprox(
      Eigen::Vector4d{0.0, 0.0, -1.0, 0.0}));
  EXPECT_TRUE(test_triangle.m_c.m_normal.isApprox(
      Eigen::Vector4d{0.0, 0.0, -1.0, 0.0}));

  test_triangle = original_triangle;
  test_triangle.m_c.m_pos = {0.0, 2.0, 0.0, 1.0};
  test_triangle.m_a.m_normal = test_triangle.getNormal();
  test_triangle.m_b.m_normal = test_triangle.getNormal();
  test_triangle.m_c.m_normal = test_triangle.getNormal();

  auto scale_matrix = Utility::getScaleMatrix({2.0, 1.0, 1.0});
  auto normal_scale_matrix = scale_matrix.inverse().transpose();
  Utility::transformTriangle(test_triangle, scale_matrix, normal_scale_matrix);

  EXPECT_TRUE(
      test_triangle.m_a.m_pos.isApprox(Eigen::Vector4d{2.0, 0.0, 1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.m_b.m_pos.isApprox(Eigen::Vector4d{2.0, 0.0, -1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.m_c.m_pos.isApprox(Eigen::Vector4d{0.0, 2.0, 0.0, 1.0}));

  EXPECT_TRUE(test_triangle.m_a.m_normal.isApprox(
      Eigen::Vector4d{1.0, 1.0, 0.0, 0.0}.normalized()));
  EXPECT_TRUE(test_triangle.m_b.m_normal.isApprox(
      Eigen::Vector4d{1.0, 1.0, 0.0, 0.0}.normalized()));
  EXPECT_TRUE(test_triangle.m_c.m_normal.isApprox(
      Eigen::Vector4d{1.0, 1.0, 0.0, 0.0}.normalized()));
}

TEST(UtilityTests, TestGetTranslationMatrix) {
  Eigen::Matrix4d transform;
  transform.setIdentity();
  transform(0, 3) = 1.0;
  transform(1, 3) = 1.0;
  transform(2, 3) = 1.0;
  EXPECT_TRUE(
      transform.isApprox(Utility::getTranslationMatrix({1.0, 1.0, 1.0})));

  transform.setIdentity();
  EXPECT_TRUE(
      transform.isApprox(Utility::getTranslationMatrix({0.0, 0.0, 0.0})));
}

TEST(UtilityTests, TestGetRotationMatrix) {
  Eigen::Matrix4d transform;
  transform.setIdentity();
  transform(0, 0) = 0.8861471;
  transform(0, 1) = 0.4459791;
  transform(0, 2) = -0.1258803;
  transform(1, 0) = -0.4623281;
  transform(1, 1) = 0.8693463;
  transform(1, 2) = -0.1746133;
  transform(2, 0) = 0.0315596;
  transform(2, 1) = 0.2129311;
  transform(2, 2) = 0.9765574;

  Eigen::Vector3d axis{3.2, -1.3, -7.5};
  const Eigen::Matrix4d &rotation = Utility::getRotationMatrix(axis, PI / 6.0);

  EXPECT_TRUE(transform.isApprox(rotation, EPSILON));
}

TEST(UtilityTests, TestGetScaleMatrix) {
  Eigen::Matrix4d transform;
  transform.setIdentity();

  EXPECT_TRUE(transform.isApprox(Utility::getScaleMatrix({1.0, 1.0, 1.0})));

  const Eigen::Vector3d scale{3.4, -9.22, 1.0};

  transform(0, 0) *= scale.x();
  transform(1, 1) *= scale.y();
  transform(2, 2) *= scale.z();
  EXPECT_TRUE(transform.isApprox(Utility::getScaleMatrix(scale)));
}

TEST(UtilityTests, TestIsEqual) {
  EXPECT_TRUE(Utility::isEqual(0.0, 0.000000099, EPSILON));
  EXPECT_FALSE(Utility::isEqual(0.0, EPSILON, EPSILON));
  EXPECT_FALSE(Utility::isEqual(0.0, 0.00000011, EPSILON));
  EXPECT_FALSE(Utility::isEqual(5.0, 8.021310011, EPSILON));
  EXPECT_TRUE(Utility::isEqual(7.8293130, 7.82931299, EPSILON));
}

TEST(UtilityTests, TestSwapByteOrder) {
  std::uint32_t bytes;
  char *const bytes_ptr = (char *)&bytes;
  bytes_ptr[0] = 'a';
  bytes_ptr[1] = 'b';
  bytes_ptr[2] = 'c';
  bytes_ptr[3] = 'd';

  const auto swapped_bytes = Utility::swapByteOrder(bytes);
  const char *const swapped_bytes_ptr = (char *)&swapped_bytes;
  EXPECT_EQ(swapped_bytes_ptr[0], 'd');
  EXPECT_EQ(swapped_bytes_ptr[1], 'c');
  EXPECT_EQ(swapped_bytes_ptr[2], 'b');
  EXPECT_EQ(swapped_bytes_ptr[3], 'a');
}
