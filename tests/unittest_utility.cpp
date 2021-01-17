#include <Eigen/Dense>

#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "utility.hpp"
#include "gtest/gtest.h"

using namespace Converter;

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
  Eigen::Vector4d a{-1.0, 0.0, 1.0, 0.0};
  Eigen::Vector4d b{1.0, 0.0, 1.0, 0.0};
  Eigen::Vector4d c{1.0, 0.0, -1.0, 0.0};
  Eigen::Vector4d d{-1.0, 0.0, -1.0, 0.0};
  Eigen::Vector4d p{0.0, 1.0, 0.0, 0.0};
  Eigen::Vector4d q{0.0, -1.0, 0.0, 0.0};

  MeshData mesh;
  mesh.m_triangles.push_back({a, b, p});
  mesh.m_triangles.push_back({b, c, p});
  mesh.m_triangles.push_back({c, d, p});
  mesh.m_triangles.push_back({d, a, p});
  mesh.m_triangles.push_back({a, q, b});
  mesh.m_triangles.push_back({b, q, c});
  mesh.m_triangles.push_back({c, q, d});
  mesh.m_triangles.push_back({d, q, a});

  Eigen::Vector4d testp{0.0, 0.0, 0.0, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -2.0, 0.0, 0.0};
  EXPECT_FALSE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -1.0, 0.0, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -1.00001, 0.0, 0.0};
  EXPECT_FALSE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, -0.99999, 0.0, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {1.0, 0.0, 1.0, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {1.0, 0.0, 0.0, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.0, 1.0, 0.0, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));

  testp = {1.00001, 0.0, 0.0, 0.0};
  EXPECT_FALSE(Utility::isPointInsideMesh(mesh, testp));

  testp = {0.3, -0.234, 0.194, 0.0};
  EXPECT_TRUE(Utility::isPointInsideMesh(mesh, testp));
}