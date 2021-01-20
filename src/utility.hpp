#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <Eigen/Dense>
#include <string>
#include <vector>

namespace Converter {

class MeshData;

namespace Utility {

void displaySupportedFormats();
std::string toLower(std::string str);
std::vector<std::string> splitString(const std::string &str);
bool startsWith(const std::string &str, const char *start);
Eigen::Matrix4d getTranslationMatrix(const Eigen::Vector3d &translation);
Eigen::Matrix4d getRotationMatrix(const Eigen::Vector3d &rotation_axis,
                                  double angle);
Eigen::Matrix4d getScaleMatrix(const Eigen::Vector3d &scale);
void transformVector(Eigen::Vector4d &point,
                     const Eigen::Matrix4d &transform_matrix);

inline bool isEqual(double a, double b, double epsilon = 0.00000001) {
  return fabs(a - b) < epsilon;
}

/*
 * Source:
 * https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time
 */
inline bool isIntegerLittleEndian() {
  static std::int16_t i = 1;
  static const char *p = (const char *)&i;
  return p[0U] == 1;
}

/*
 * This is needed to be checked separately because according to the referred
 * article on this page:
 * https://en.wikipedia.org/wiki/Endianness#Floating-point_and_endianness
 * it can differ from integer representation.
 */
inline bool isFloatLittleEndian() {
  static const float i = -1.0f;
  static const char *p = (const char *)&i;
  return p[0U] == 0;
}

/*
 * Source: https://stackoverflow.com/a/24761663
 */
template <typename T> T swapByteOrder(const T &data) {
  T return_value;
  char *p_data = (char *)&data;
  char *p_return_value = (char *)&return_value;
  std::size_t size = sizeof(T);

  for (std::size_t i = 0U; i < size; ++i) {
    p_return_value[size - 1 - i] = p_data[i];
  }

  return return_value;
}

} // namespace Utility
} // namespace Converter

#endif