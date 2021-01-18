#include <Eigen/Dense>

#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "utility.hpp"
#include "gtest/gtest.h"

using namespace Converter;

namespace {

static constexpr double PI = 3.141592653589793238;
static constexpr double EPSILON = 0.0000001;

}

TEST(UtilityTests, TestRayTriangleIntersection) {
  Eigen::Vector4d a{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d b{-1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d c{0.0, 1.0, 1.0, 1.0};
  Triangle triangle{a, b, c};

  Eigen::Vector4d ray_start_point{0.0, 0.0, 0.5, 1.0};
  Eigen::Vector4d ray_dir{0.0, -1.0, 0.0, 0.0};
  auto hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_FALSE(hit);

  ray_start_point = {0.0, 0.0, 0.5, 1.0};
  ray_dir= {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(Eigen::Vector4d{0.0, 1.0, 0.5, 1.0}));

  ray_start_point = {1.0, 0.0, 0.0, 1.0};
  ray_dir= {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(a));

  ray_start_point = {1.001, 0.0, 0.0, 1.0};
  ray_dir= {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_FALSE(hit);

  ray_start_point = {0.0, 1.0, 0.5, 1.0};
  ray_dir= {0.0, 1.0, 0.0, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(ray_start_point));

  ray_start_point = {0.2, 0.1, 0.4, 1.0};
  ray_dir= {-0.3, 0.8, -0.2, 0.0};
  hit = Utility::rayTriangleIntersection(ray_start_point, ray_dir, triangle);
  EXPECT_TRUE(hit.value().isApprox(Eigen::Vector4d{-0.1375, 1.0, 0.175, 1.0}));
}

TEST(UtilityTests, TestIsPointInsideMesh) {
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

TEST(UtilityTests, TestTransformVector) {
  Eigen::Vector4d point;

  // pure rotations
  point = {1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d rotation_matrix =
      Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{0.0, 0.0, -1.0, 1.0}));
  
  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix =
      Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI);
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
  rotation_matrix =
      Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  translation_matrix = Utility::getTranslationMatrix({1.0, -1.0, 0.0});
  
  const Eigen::Matrix4d &transformation_matrix =
      translation_matrix * rotation_matrix * scale_matrix;

  Utility::transformVector(point, transformation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{1.0, -1.0, -2.0, 1.0}));
}

TEST(UtilityTests, TestTransformTriangle) {
  // Eigen::Vector4d a{-1.0, 0.0, 0.0, 1.0};
  // Eigen::Vector4d b{1.0, 0.0, 0.0, 1.0};
  // Eigen::Vector4d c{0.0, 2.0, 0.0, 1.0};

  // Triangle original_triangle{a, b, c};
  // original_triangle.m_a.m_normal = original_triangle.getNormal();
  // original_triangle.m_b.m_normal = original_triangle.getNormal();
  // original_triangle.m_c.m_normal = original_triangle.getNormal();

  // Triangle test_1_tri = original_triangle;
  // Utility::transformTriangle();
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
}