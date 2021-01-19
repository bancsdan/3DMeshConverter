#include <Eigen/Dense>

#include "geometry/triangle.hpp"
#include "gtest/gtest.h"

using namespace Converter;

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
  EXPECT_TRUE(t1 == t2);

  t2.m_c.m_pos[2] = 8.9;
  EXPECT_FALSE(t1 == t2);
}