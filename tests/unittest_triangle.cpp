#include <Eigen/Dense>

#include "geometry/triangle.hpp"
#include "utility.hpp"
#include "gtest/gtest.h"

using namespace Converter;

namespace {

static constexpr double PI = 3.141592653589793238;

}

TEST(TriangleTests, TestGetArea) {
  Triangle t1(Eigen::Vector4d{0.0, 0.0, 0.0, 1.0},
              Eigen::Vector4d{1.0, 0.0, 0.0, 1.0},
              Eigen::Vector4d{0.0, 1.0, 0.0, 1.0});
  EXPECT_DOUBLE_EQ(0.5, t1.getArea());

  Triangle t2(Eigen::Vector4d{0.0, 0.0, 0.0, 1.0},
              Eigen::Vector4d{0.0, 0.0, 0.0, 1.0},
              Eigen::Vector4d{0.0, 0.0, 0.0, 1.0});
  EXPECT_DOUBLE_EQ(0.0, t2.getArea());

  Triangle t3(Eigen::Vector4d{3.923, 9.123, 4.41231, 1.0},
              Eigen::Vector4d{5.231, 4.16923, 8.739, 1.0},
              Eigen::Vector4d{11.684, 2.985, 1.194, 1.0});
  EXPECT_DOUBLE_EQ(32.2470688496687, t3.getArea());
}

TEST(TriangleTests, TestGetNormal) {
  Triangle t1(Eigen::Vector4d{0.0, 0.0, 0.0, 0.0},
              Eigen::Vector4d{1.0, 0.0, 0.0, 0.0},
              Eigen::Vector4d{0.0, 1.0, 0.0, 0.0});
  EXPECT_TRUE(t1.getNormal().isApprox(Eigen::Vector4d{0.0, 0.0, 1.0, 0.0}));
}

TEST(TriangleTests, TestEqualityOperator) {
  Triangle t1(Eigen::Vector4d{3.923, 9.123, 4.41231, 1.0},
              Eigen::Vector4d{5.231, 4.16923, 8.739, 1.0},
              Eigen::Vector4d{11.684, 2.985, 1.194, 1.0});
  Triangle t2 = t1;
  EXPECT_EQ(t1, t2);

  t2.c.pos[2U] = 8.9;
  EXPECT_FALSE(t1 == t2);
}

TEST(TriangleTests, TestRayIntersection) {
  Eigen::Vector4d a{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d b{-1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d c{0.0, 1.0, 1.0, 1.0};
  Triangle triangle{a, b, c};

  Eigen::Vector4d ray_start_point{0.0, 0.0, 0.5, 1.0};
  Eigen::Vector4d ray_dir{0.0, -1.0, 0.0, 0.0};
  auto hit = triangle.rayIntersection(ray_start_point, ray_dir);
  EXPECT_FALSE(hit.has_value());

  ray_start_point = {0.0, 0.0, 0.5, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = triangle.rayIntersection(ray_start_point, ray_dir);
  EXPECT_TRUE(hit->isApprox(Eigen::Vector4d{0.0, 1.0, 0.5, 1.0}));

  ray_start_point = {1.0, 0.0, 0.0, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = triangle.rayIntersection(ray_start_point, ray_dir);
  EXPECT_TRUE(hit->isApprox(a));

  ray_start_point = {1.001, 0.0, 0.0, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = triangle.rayIntersection(ray_start_point, ray_dir);
  EXPECT_FALSE(hit.has_value());

  ray_start_point = {0.0, 1.0, 0.5, 1.0};
  ray_dir = {0.0, 1.0, 0.0, 0.0};
  hit = triangle.rayIntersection(ray_start_point, ray_dir);
  EXPECT_TRUE(hit->isApprox(ray_start_point));

  ray_start_point = {0.2, 0.1, 0.4, 1.0};
  ray_dir = {-0.3, 0.8, -0.2, 0.0};
  hit = triangle.rayIntersection(ray_start_point, ray_dir);
  EXPECT_TRUE(hit->isApprox(Eigen::Vector4d{-0.1375, 1.0, 0.175, 1.0}));
}

TEST(TriangleTests, TestIsInside) {
  Eigen::Vector4d a{1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d b{-1.0, 1.0, 0.0, 1.0};
  Eigen::Vector4d c{0.0, 1.0, 1.0, 1.0};
  Triangle triangle{a, b, c};

  EXPECT_TRUE(triangle.isInside(a));
  EXPECT_TRUE(triangle.isInside(b));
  EXPECT_TRUE(triangle.isInside(c));

  Eigen::Vector4d a_moved{1.0001, 1.0, 0.0, 1.0};
  EXPECT_FALSE(triangle.isInside(a_moved));
  Eigen::Vector4d b_moved{-1.0001, 1.0, 0.0, 1.0};
  EXPECT_FALSE(triangle.isInside(b_moved));
  Eigen::Vector4d c_moved{0, 1.0, 1.1, 1.0};
  EXPECT_FALSE(triangle.isInside(c_moved));

  Eigen::Vector4d d{0, 1.0, 0.5, 1.0};
  EXPECT_TRUE(triangle.isInside(d));
  Eigen::Vector4d d_moved = {0, 1.1, 0.5, 1.0};
  EXPECT_FALSE(triangle.isInside(d_moved));

  a = {0.0, 1.0, 0.0, 1.0};
  b = {1.0, 0.0, 0.0, 1.0};
  c = {1.0, 0.0, -11.0, 1.0};
  triangle = {a, b, c};
  EXPECT_FALSE(triangle.isInside({0.5, 0.5001, -0.1, 1.0}));
  EXPECT_TRUE(triangle.isInside({0.5, 0.5, -0.1, 1.0}));
}

TEST(UtilityTests, TestTransformTriangle) {
  Eigen::Vector4d a{1.0, 0.0, 1.0, 1.0};
  Eigen::Vector4d b{1.0, 0.0, -1.0, 1.0};
  Eigen::Vector4d c{1.0, 2.0, 0.0, 1.0};

  Triangle original_triangle{a, b, c};
  original_triangle.a.normal = original_triangle.getNormal();
  original_triangle.b.normal = original_triangle.getNormal();
  original_triangle.c.normal = original_triangle.getNormal();

  Triangle test_triangle = original_triangle;
  auto rotation_matrix = Utility::getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  auto normal_rotation_matrix = rotation_matrix.inverse().transpose();
  test_triangle.transform(rotation_matrix, normal_rotation_matrix);

  EXPECT_TRUE(
      test_triangle.a.pos.isApprox(Eigen::Vector4d{1.0, 0.0, -1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.b.pos.isApprox(Eigen::Vector4d{-1.0, 0.0, -1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.c.pos.isApprox(Eigen::Vector4d{0.0, 2.0, -1.0, 1.0}));

  EXPECT_TRUE(
      test_triangle.a.normal.isApprox(Eigen::Vector4d{0.0, 0.0, -1.0, 0.0}));
  EXPECT_TRUE(
      test_triangle.b.normal.isApprox(Eigen::Vector4d{0.0, 0.0, -1.0, 0.0}));
  EXPECT_TRUE(
      test_triangle.c.normal.isApprox(Eigen::Vector4d{0.0, 0.0, -1.0, 0.0}));

  test_triangle = original_triangle;
  test_triangle.c.pos = {0.0, 2.0, 0.0, 1.0};
  test_triangle.a.normal = test_triangle.getNormal();
  test_triangle.b.normal = test_triangle.getNormal();
  test_triangle.c.normal = test_triangle.getNormal();

  auto scale_matrix = Utility::getScaleMatrix({2.0, 1.0, 1.0});
  auto normal_scale_matrix = scale_matrix.inverse().transpose();
  test_triangle.transform(scale_matrix, normal_scale_matrix);

  EXPECT_TRUE(
      test_triangle.a.pos.isApprox(Eigen::Vector4d{2.0, 0.0, 1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.b.pos.isApprox(Eigen::Vector4d{2.0, 0.0, -1.0, 1.0}));
  EXPECT_TRUE(
      test_triangle.c.pos.isApprox(Eigen::Vector4d{0.0, 2.0, 0.0, 1.0}));

  EXPECT_TRUE(test_triangle.a.normal.isApprox(
      Eigen::Vector4d{1.0, 1.0, 0.0, 0.0}.normalized()));
  EXPECT_TRUE(test_triangle.b.normal.isApprox(
      Eigen::Vector4d{1.0, 1.0, 0.0, 0.0}.normalized()));
  EXPECT_TRUE(test_triangle.c.normal.isApprox(
      Eigen::Vector4d{1.0, 1.0, 0.0, 0.0}.normalized()));
}