#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <Eigen/Dense>
#include <math.h>
#include <string>
#include <vector>

namespace Converter {

class MeshData;

namespace Utility {

/**
 * @brief Writes the supported input and output formats to stdout.
 */
void displaySupportedFormats();

/**
 * @brief Converts uppercase characters in a string to lowercase.
 * @param str The string to be converted.
 * @return The converted string.
 */
std::string toLower(std::string str);

/**
 * @brief Splits the string by whitespace.
 * @param str The string to be split.
 * @return A vector containing the strings.
 */
std::vector<std::string> splitString(const std::string &str);

/**
 * @brief Determines if a string starts with another.
 * @param str The string that should be checked for the starting pattern.
 * @param start The C syle character sequence that should be matched.
 * @return True if str starts with start, otherwise false.
 */
bool startsWith(const std::string &str, const char *start);

/**
 * @brief Constructs and returns a translation matrix.
 * @param translation A vector containing the x, y and z amount of
 * translation.
 * @return A matrix containing the translation matrix.
 */
Eigen::Matrix4d getTranslationMatrix(const Eigen::Vector3d &translation);

/**
 * @brief Constructs and returns a rotation matrix.
 * @param rotation_axis A vector containing the x, y and z
 * direction of the axis, taken from the origin.
 * @param angle The angle in radians that the result matrix should rotate
 * with.
 * @return A matrix containing the rotation matrix.
 */
Eigen::Matrix4d getRotationMatrix(const Eigen::Vector3d &rotation_axis,
                                  double angle);

/**
 * @brief Constructs and returns a scale matrix.
 * @param scale A vector containing the x, y and z amount of scaling.
 * @note Default values are 1.0 for all directions.
 * @return A matrix containing the scale matrix.
 */
Eigen::Matrix4d getScaleMatrix(const Eigen::Vector3d &scale);
void transformVector(Eigen::Vector4d &point,
                     const Eigen::Matrix4d &transform_matrix);

/**
 * @brief Checks if two dobules are equal.
 * @param a The first double to be compared.
 * @param b The second double to be compared.
 * @param epsilon The threshold for the difference of the values, under
 * which they should be considered equal. Default value is 0.00000001.
 */
inline bool isEqual(double a, double b, double epsilon = 0.00000001) {
  return fabs(a - b) < epsilon;
}

/**
 * @brief Checks if the system stores integers in a little endian format.
 * @note Source:
 * https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time
 * @return True if the format is little endian, otherwise false.
 */
inline bool isIntegerLittleEndian() {
  static std::int16_t i = 1;
  static const char *p = (const char *)&i;
  return p[0U] == 1;
}

/**
 * @brief Checks if the system stores floats in a little endian format.
 * @note This is needed to be checked separately because according to the
 * referred article on this page:
 * https://en.wikipedia.org/wiki/Endianness#Floating-point_and_endianness
 * it can differ from integer representation.
 * @return True if the format is little endian, otherwise false.
 */
inline bool isFloatLittleEndian() {
  static const float i = -1.0f;
  static const char *p = (const char *)&i;
  return p[0U] == 0;
}

/**
 * @brief Swaps the byte order of the passed object.
 * @note Source: https://stackoverflow.com/a/24761663
 * @tparam The type of the passed value.
 * @param data The object whose bytes should be swapped.
 * @return An object of type T whose byte representation in memory
 * is swapped compared to the input value.
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