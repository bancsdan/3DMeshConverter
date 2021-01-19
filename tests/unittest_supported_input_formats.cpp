#include <string>

#include "reader/supported_input_formats.hpp"
#include "gtest/gtest.h"

namespace Converter {

TEST(SupportedInputFormatsTests, TestConvertInputFormatToEnum) {
  std::string format = ".obj";
  EXPECT_EQ(Reader::convertInputFormatToEnum(format), Reader::InputFormat::OBJ);
  format = ".exe";
  EXPECT_EQ(Reader::convertInputFormatToEnum(format),
            Reader::InputFormat::INVALID);
}

} // namespace Converter