#include <Eigen/Dense>

#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "utility.hpp"
#include "gtest/gtest.h"

using namespace Converter;

static constexpr double PI = 3.141592653589793238;
static constexpr double EPSILON = 0.0000001;

TEST(UtilityTests, TestDoesRayIntersectTriangle) {
  //   Triangle t1(Eigen::Vector4d{1.0, 1.0, 0.0, 0.0},
  //               Eigen::Vector4d{0.0, 1.0, 1.0, 0.0},
  //               Eigen::Vector4d{0.0, 1.0, -1.0, 0.0});

  //   Eigen::Vector4d p1{0.5, 0.0, 0.0, 0.0};
  //   Eigen::Vector4d ray_dir{0.0, 1.0, 0.0, 0.0};
  //   EXPECT_TRUE(Utility::rayTriangleIntersection(p1, ray_dir, t1));

  //   ray_dir = {0.0, -1.0, 0.0, 0.0};
  //   EXPECT_FALSE(Utility::doesRayIntersectTriangle(p1, ray_dir, t1));

  //   ray_dir = {1.0, 0.0, 0.0, 0.0};
  //   EXPECT_FALSE(Utility::doesRayIntersectTriangle(p1, ray_dir, t1));

  //   ray_dir = {-1.0, 0.5, 0.0, 0.0};
  //   EXPECT_FALSE(Utility::doesRayIntersectTriangle(p1, ray_dir, t1));

  //   p1 = {1.0, 0.0, 0.0, 0.0};
  //   ray_dir = {0.0, 1.0, 0.0, 0.0};
  //   EXPECT_TRUE(Utility::doesRayIntersectTriangle(p1, ray_dir, t1));

  //   p1 = {1.0001, 0.0, 0.0, 0.0};
  //   EXPECT_FALSE(Utility::doesRayIntersectTriangle(p1, ray_dir, t1));

  //   p1 = {0.9999, 0.0, 0.0, 0.0};
  //   EXPECT_TRUE(Utility::doesRayIntersectTriangle(p1, ray_dir, t1));
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

TEST(UtilityTest, TestGetTranslationMatrix) {
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

TEST(UtilityTest, TestGetRotationMatrix) {
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

TEST(UtilityTest, TestGetScaleMatrix) {
  Eigen::Matrix4d transform;
  transform.setIdentity();

  EXPECT_TRUE(transform.isApprox(Utility::getScaleMatrix({1.0, 1.0, 1.0})));

  const Eigen::Vector3d scale{3.4, -9.22, 1.0};

  transform(0, 0) *= scale.x();
  transform(1, 1) *= scale.y();
  transform(2, 2) *= scale.z();
  EXPECT_TRUE(transform.isApprox(Utility::getScaleMatrix(scale)));
}

TEST(UtilityTest, TestTransformVector) {
  Eigen::Vector4d point{-1.0, 0.0, 0.0, 1.0};

  // pure rotations
  Eigen::Matrix4d rotation_matrix =
      Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{1.0, 0.0, 0.0, 1.0}));

  rotation_matrix = Utility::getRotationMatrix({0.0, 0.0, 1.0}, PI);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  rotation_matrix = Utility::getRotationMatrix({1.0, 0.0, 0.0}, PI);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  rotation_matrix = Utility::getRotationMatrix({8.213, -5.231, 1.894}, 0.0);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  rotation_matrix =
      Utility::getRotationMatrix({8.213, -5.231, 1.894}, PI / 5.0);
  Utility::transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(
      Eigen::Vector4d{-0.939931, -0.0288444, -0.340144, 1.0}, EPSILON));

  // pure translations
  point = {-1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d translation_matrix =
      Utility::getTranslationMatrix({0.0, 1.0, 0.0});
  Utility::transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 1.0, 0.0, 1.0}));

  translation_matrix = Utility::getTranslationMatrix({1.0, -1.0, 0.0});
  Utility::transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{0.0, 0.0, 0.0, 1.0}));

  translation_matrix = Utility::getTranslationMatrix({3.9123, -5.123, 11.0092});
  Utility::transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{3.9123, -5.123, 11.0092, 1.0}));

  // pure scaling
  point = {-1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d scale_matrix = Utility::getScaleMatrix({1.0, 1.0, 1.0});
  Utility::transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  scale_matrix = Utility::getScaleMatrix({0.5, 0.5, 0.5});
  Utility::transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-0.5, 0.0, 0.0, 1.0}));
}

TEST(UtilityTest, TestTransformTriangle) {
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

TEST(UtilityTests, TestRotate) {
  // static constexpr double PI = 3.141592653589;

  // Eigen::Vector4d testp{1.0, 0.0, 0.0, 1.0};
  // Eigen::Vector3d axis{0.0, 1.0, 0.0};
  // double angle =  PI / 2.0;
  // Utility::getRotationMatrix(axis, angle);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(0.0, 0.0, -1.0, 1.0)));

  // testp = {1.0, 0.0, 0.0, 1.0};
  // axis = {0.0, 0.0, 1.0};
  // angle =  PI / 2.0;
  // Utility::rotate(testp, axis, angle);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(0.0, 1.0, 0.0, 1.0)));

  // testp = {1.0, 0.0, 0.0, 1.0};
  // axis = {2.0, 1.0, -0.5};
  // angle =  PI / 6.0;
  // Utility::rotate(testp, axis, angle);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(0.968101286615, -0.058071003702,
  // -0.243736860944, 1.0)));

  // testp = {72.98123, -9.8230, -5.9123, 1.0};
  // axis = {-3.21231, 4.1231, 2.598329};
  // angle =  PI / 13.0;
  // Utility::rotate(testp, axis, angle);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(71.702884115833,
  // -3.5623037120199, -17.427362231201, 1.0)));
}

TEST(UtilityTests, TestTranslate) {
  // Eigen::Vector4d testp{1.0, 0.0, 0.0, 1.0};
  // Eigen::Vector4d translation_vect{-1.0, 0.0, 0.0, 0.0};
  // Utility::translate(testp, translation_vect);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(0.0, 0.0, 0.0, 1.0)));

  // testp = {0.0, 0.0, 0.0, 1.0};
  // translation_vect = {8.98123, -689.123, 82.1232, 0.0};
  // Utility::translate(testp, translation_vect);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(8.98123,
  // -689.123, 82.1232, 1.0)));

  // testp = {8.98123, -689.123, 82.1232, 1.0};
  // translation_vect = {0.0, 0.0, 0.0, 0.0};
  // Utility::translate(testp, translation_vect);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(8.98123,
  // -689.123, 82.1232, 1.0)));
}

TEST(UtilityTests, TestScale) {
  // Eigen::Vector4d testp{1.0, 0.0, 0.0, 1.0};
  // Eigen::Vector4d translation_vect{-1.0, 0.0, 0.0, 0.0};
  // Utility::translate(testp, translation_vect);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(0.0, 0.0, 0.0, 1.0)));

  // testp = {0.0, 0.0, 0.0, 1.0};
  // translation_vect = {8.98123, -689.123, 82.1232, 0.0};
  // Utility::translate(testp, translation_vect);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(8.98123,
  // -689.123, 82.1232, 1.0)));

  // testp = {8.98123, -689.123, 82.1232, 1.0};
  // translation_vect = {0.0, 0.0, 0.0, 0.0};
  // Utility::translate(testp, translation_vect);
  // EXPECT_TRUE(testp.isApprox(Eigen::Vector4d(8.98123,
  // -689.123, 82.1232, 1.0)));
}