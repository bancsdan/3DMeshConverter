#include <Eigen/Dense>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "exception.hpp"
#include "reader/supported_input_formats.hpp"
#include "utility.hpp"
#include "writer/supported_output_formats.hpp"

namespace Converter {

namespace Utility {

void displaySupportedFormats() {
  std::cout << "Currently supported input filetypes:" << std::endl;
  for (const auto &format_pair : Reader::supported_input_formats_map) {
    std::cout << "\t" << format_pair.first << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Currently supported output filetypes:" << std::endl;
  for (const auto &format_pair : Writer::supported_output_formats_map) {
    std::cout << "\t" << format_pair.first << std::endl;
  }
  std::cout << std::endl;
}

std::string toLower(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](std::string::value_type c) {
                   return static_cast<std::string::value_type>(std::tolower(c));
                 });
  return str;
}

std::vector<std::string> splitString(const std::string &str) {
  std::istringstream buffer(str);
  std::vector<std::string> result{std::istream_iterator<std::string>(buffer),
                                  std::istream_iterator<std::string>()};
  return result;
}

bool startsWith(const std::string &str, const char *start) {
  return str.rfind(start, 0U) == 0U;
}

void transformVector(Eigen::Vector4d &point,
                     const Eigen::Matrix4d &transform_matrix) {
  point = transform_matrix * point;
}

Eigen::Matrix4d getTranslationMatrix(const Eigen::Vector3d &translation) {
  Eigen::Matrix4d translation_matrix;
  translation_matrix.setIdentity();
  translation_matrix(0, 3) = translation.x();
  translation_matrix(1, 3) = translation.y();
  translation_matrix(2, 3) = translation.z();

  return translation_matrix;
}

Eigen::Matrix4d getRotationMatrix(const Eigen::Vector3d &rotation_axis,
                                  double angle) {
  Eigen::Matrix4d rotation_matrix;
  rotation_matrix.setIdentity();
  rotation_matrix.block<3, 3>(0, 0) =
      Eigen::AngleAxisd(angle, rotation_axis.normalized()).matrix();

  return rotation_matrix;
}

Eigen::Matrix4d getScaleMatrix(const Eigen::Vector3d &scale) {
  Eigen::Matrix4d scale_matrix;
  scale_matrix.setIdentity();
  scale_matrix(0, 0) *= scale.x();
  scale_matrix(1, 1) *= scale.y();
  scale_matrix(2, 2) *= scale.z();

  return scale_matrix;
}

} // namespace Utility
} // namespace Converter