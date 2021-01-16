#ifndef READER_FACTORY_HPP
#define READER_FACTORY_HPP

#include <memory>

#include "ireader.hpp"
#include "supported_input_formats.hpp"

namespace Converter {

class ReaderFactory {
 public:
  [[nodiscard]] static std::unique_ptr<IReader> createReader(
      Reader::InputFormat format);
};

}  // namespace Converter

#endif