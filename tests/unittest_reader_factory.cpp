#include <string>

#include "reader/reader_factory.hpp"
#include "reader/supported_input_formats.hpp"
#include "gtest/gtest.h"

using namespace Converter;

TEST(ReaderFactoryTests, TestCreateReader) {
  Reader::InputFormat invalid = Reader::InputFormat::INVALID;
  Reader::InputFormat obj = Reader::InputFormat::OBJ;

  EXPECT_FALSE(ReaderFactory::createReader(invalid));
  EXPECT_TRUE(ReaderFactory::createReader(obj));
}
