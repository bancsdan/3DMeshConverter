#include <string>

#include "writer/supported_output_formats.hpp"
#include "gtest/gtest.h"

using namespace Converter;

TEST(SupportedOutputFormatsTests, TestConvertOutputFormatToEnum) {
  std::string format = ".stl";
  EXPECT_EQ(Writer::convertOutputFormatToEnum(format),
            Writer::OutputFormat::STL);
  format = ".exe";
  EXPECT_EQ(Writer::convertOutputFormatToEnum(format),
            Writer::OutputFormat::INVALID);
}
