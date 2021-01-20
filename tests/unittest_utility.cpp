#include <Eigen/Dense>
#include <cstdint>
#include <string>

#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "utility.hpp"
#include "gtest/gtest.h"

using namespace Converter;
using namespace Utility;

namespace {

static constexpr double PI = 3.141592653589793238;
static constexpr double EPSILON = 0.0000001;

} // namespace

TEST(UtilityTests, TestToLower) {
  std::string str{"ABCdef123$!"};
  EXPECT_EQ(toLower(str), "abcdef123$!");

  str = "";
  EXPECT_EQ(toLower(str), "");
}

TEST(UtilityTests, TestSplitString) {
  std::vector<std::string> expected_result{"Abc", "def", "ghi!"};

  auto result = splitString("Abc def ghi!");
  EXPECT_EQ(result, expected_result);

  result = splitString("Abc def  ghi!");
  EXPECT_EQ(result, expected_result);

  expected_result = {};
  expected_result.push_back("Abc");
  result = splitString("Abc");
  EXPECT_EQ(result, expected_result);
}

TEST(UtilityTests, TestStartsWith) {
  std::string str{"Abc!de"};

  EXPECT_TRUE(startsWith(str, "A"));
  EXPECT_TRUE(startsWith(str, "Abc!"));
  EXPECT_TRUE(startsWith(str, "Abc!de"));
  EXPECT_FALSE(startsWith(str, "Abc!def"));
  EXPECT_FALSE(startsWith(str, "bc"));
}

TEST(UtilityTests, TestTransformVector) {
  Eigen::Vector4d point;

  // pure rotations
  point = {1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d rotation_matrix =
      getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{0.0, 0.0, -1.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = getRotationMatrix({0.0, 1.0, 0.0}, PI);
  transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{1.0, 0.0, 0.0, 1.0}));

  point = {1.0, 0.0, 0.0, 1.0};
  rotation_matrix = getRotationMatrix({0.0, 0.0, 1.0}, PI);
  transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = getRotationMatrix({1.0, 0.0, 0.0}, PI);
  transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = getRotationMatrix({8.213, -5.231, 1.894}, 0.0);
  transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  rotation_matrix = getRotationMatrix({8.213, -5.231, 1.894}, PI / 5.0);
  transformVector(point, rotation_matrix);
  EXPECT_TRUE(point.isApprox(
      Eigen::Vector4d{-0.939931, -0.0288444, -0.340144, 1.0}, EPSILON));

  // pure translations
  point = {-1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d translation_matrix = getTranslationMatrix({0.0, 0.0, 0.0});
  transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 1.0, 0.0, 1.0};
  translation_matrix = getTranslationMatrix({1.0, -1.0, 0.0});
  transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{0.0, 0.0, 0.0, 1.0}));

  point = {0.0, 0.0, 0.0, 1.0};
  translation_matrix = getTranslationMatrix({3.9123, -5.123, 11.0092});
  transformVector(point, translation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{3.9123, -5.123, 11.0092, 1.0}));

  // pure scaling
  point = {-1.0, 0.0, 0.0, 1.0};
  Eigen::Matrix4d scale_matrix = getScaleMatrix({1.0, 1.0, 1.0});
  transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-1.0, 0.0, 0.0, 1.0}));

  point = {-1.0, 0.0, 0.0, 1.0};
  scale_matrix = getScaleMatrix({0.5, 0.5, 0.5});
  transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{-0.5, 0.0, 0.0, 1.0}));

  point = {1.0, 1.0, 1.0, 1.0};
  scale_matrix = getScaleMatrix({5.92, -12.0, 3.08});
  transformVector(point, scale_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{5.92, -12.0, 3.08, 1.0}));

  // combined
  point = {1.0, 0.0, 0.0, 1.0};
  scale_matrix = getScaleMatrix({2.0, 1.0, 1.0});
  rotation_matrix = getRotationMatrix({0.0, 1.0, 0.0}, PI / 2.0);
  translation_matrix = getTranslationMatrix({1.0, -1.0, 0.0});

  const Eigen::Matrix4d &transformation_matrix =
      translation_matrix * rotation_matrix * scale_matrix;

  transformVector(point, transformation_matrix);
  EXPECT_TRUE(point.isApprox(Eigen::Vector4d{1.0, -1.0, -2.0, 1.0}));
}

TEST(UtilityTests, TestGetTranslationMatrix) {
  Eigen::Matrix4d transform;
  transform.setIdentity();
  transform(0, 3) = 1.0;
  transform(1, 3) = 1.0;
  transform(2, 3) = 1.0;
  EXPECT_TRUE(transform.isApprox(getTranslationMatrix({1.0, 1.0, 1.0})));

  transform.setIdentity();
  EXPECT_TRUE(transform.isApprox(getTranslationMatrix({0.0, 0.0, 0.0})));
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
  const Eigen::Matrix4d &rotation = getRotationMatrix(axis, PI / 6.0);

  EXPECT_TRUE(transform.isApprox(rotation, EPSILON));
}

TEST(UtilityTests, TestGetScaleMatrix) {
  Eigen::Matrix4d transform;
  transform.setIdentity();

  EXPECT_TRUE(transform.isApprox(getScaleMatrix({1.0, 1.0, 1.0})));

  const Eigen::Vector3d scale{3.4, -9.22, 1.0};

  transform(0, 0) *= scale.x();
  transform(1, 1) *= scale.y();
  transform(2, 2) *= scale.z();
  EXPECT_TRUE(transform.isApprox(getScaleMatrix(scale)));
}

TEST(UtilityTests, TestIsEqual) {
  EXPECT_TRUE(isEqual(0.0, 0.000000099, EPSILON));
  EXPECT_FALSE(isEqual(0.0, EPSILON, EPSILON));
  EXPECT_FALSE(isEqual(0.0, 0.00000011, EPSILON));
  EXPECT_FALSE(isEqual(5.0, 8.021310011, EPSILON));
  EXPECT_TRUE(isEqual(7.8293130, 7.82931299, EPSILON));
}

TEST(UtilityTests, TestSwapByteOrder) {
  std::uint32_t bytes;
  char *const bytes_ptr = (char *)&bytes;
  bytes_ptr[0U] = 'a';
  bytes_ptr[1U] = 'b';
  bytes_ptr[2U] = 'c';
  bytes_ptr[3U] = 'd';

  const auto swapped_bytes = swapByteOrder(bytes);
  const char *const swapped_bytes_ptr = (char *)&swapped_bytes;
  EXPECT_EQ(swapped_bytes_ptr[0U], 'd');
  EXPECT_EQ(swapped_bytes_ptr[1U], 'c');
  EXPECT_EQ(swapped_bytes_ptr[2U], 'b');
  EXPECT_EQ(swapped_bytes_ptr[3U], 'a');
}
