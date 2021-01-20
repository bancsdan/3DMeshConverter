#include <Eigen/Dense>

#include "gtest/gtest.h"
#include "geometry/meshdata.hpp"

class MeshDataTests : public ::testing::Test {
protected:
  static constexpr double PI = 3.141592653589793238;
  static constexpr double EPSILON = 0.0000001;
  MeshData cube;
  MeshData double_pyramid;

  void SetUp() {
    {
      Eigen::Vector4d a{-1.0, -1.0, 1.0, 1.0};
      Eigen::Vector4d b{1.0, -1.0, 1.0, 1.0};
      Eigen::Vector4d c{1.0, 1.0, 1.0, 1.0};
      Eigen::Vector4d d{-1.0, 1.0, 1.0, 1.0};
      Eigen::Vector4d e{1.0, -1.0, -1.0, 1.0};
      Eigen::Vector4d f{-1.0, -1.0, -1.0, 1.0};
      Eigen::Vector4d g{-1.0, 1.0, -1.0, 1.0};
      Eigen::Vector4d h{1.0, 1.0, -1.0, 1.0};
      cube.triangles.push_back({a, b, c});
      cube.triangles.push_back({a, c, d});
      cube.triangles.push_back({b, e, h});
      cube.triangles.push_back({b, h, c});
      cube.triangles.push_back({e, f, g});
      cube.triangles.push_back({e, g, h});
      cube.triangles.push_back({f, a, d});
      cube.triangles.push_back({f, d, g});
      cube.triangles.push_back({d, c, h});
      cube.triangles.push_back({d, h, g});
      cube.triangles.push_back({f, e, b});
      cube.triangles.push_back({f, b, a});
    }
    {
      Eigen::Vector4d a{-1.0, 0.0, 1.0, 1.0};
      Eigen::Vector4d b{1.0, 0.0, 1.0, 1.0};
      Eigen::Vector4d c{1.0, 0.0, -1.0, 1.0};
      Eigen::Vector4d d{-1.0, 0.0, -1.0, 1.0};
      Eigen::Vector4d p{0.0, 1.0, 0.0, 1.0};
      Eigen::Vector4d q{0.0, -1.0, 0.0, 1.0};

      double_pyramid.triangles.push_back({a, b, p});
      double_pyramid.triangles.push_back({b, c, p});
      double_pyramid.triangles.push_back({c, d, p});
      double_pyramid.triangles.push_back({d, a, p});
      double_pyramid.triangles.push_back({a, q, b});
      double_pyramid.triangles.push_back({b, q, c});
      double_pyramid.triangles.push_back({c, q, d});
      double_pyramid.triangles.push_back({d, q, a});
    }
  }
};

TEST_F(MeshDataTests, TestCalculateSurfaceArea) {
  EXPECT_DOUBLE_EQ(cube.calculateMeshSurfaceArea(), 24.0);
  EXPECT_DOUBLE_EQ(double_pyramid.calculateMeshSurfaceArea(), 11.31370849898476);
}

TEST_F(MeshDataTests, TestCalculateVolume) {
  EXPECT_DOUBLE_EQ(double_pyramid.calculateMeshVolume(), 8.0 / 3.0);
  EXPECT_DOUBLE_EQ(cube.calculateMeshVolume(), 8.0);
}

TEST_F(MeshDataTests, TestIsPointInsideMesh) {
  Eigen::Vector4d testp{0.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));

  testp = {0.0, -2.0, 0.0, 1.0};
  EXPECT_FALSE(double_pyramid.isPointInside(testp));

  testp = {0.0, -1.0, 0.0, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));

  testp = {0.0, -1.00001, 0.0, 1.0};
  EXPECT_FALSE(double_pyramid.isPointInside(testp));

  testp = {0.0, -0.99999, 0.0, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));

  testp = {1.0, 0.0, 1.0, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));

  testp = {1.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));

  testp = {0.0, 1.0, 0.0, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));

  testp = {1.00001, 0.0, 0.0, 1.0};
  EXPECT_FALSE(double_pyramid.isPointInside(testp));

  testp = {0.29684, -0.234, 0.194, 1.0};
  EXPECT_TRUE(double_pyramid.isPointInside(testp));
}
