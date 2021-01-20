#include <string>

#include "writer/supported_output_formats.hpp"
#include "writer/writer_factory.hpp"
#include "gtest/gtest.h"

using namespace Converter;

TEST(WriterFactoryTests, TestCreateWriter) {
  Writer::OutputFormat invalid = Writer::OutputFormat::INVALID;
  Writer::OutputFormat stl = Writer::OutputFormat::STL;

  EXPECT_EQ(WriterFactory::createWriter(invalid), nullptr);
  EXPECT_TRUE(WriterFactory::createWriter(stl));
}
