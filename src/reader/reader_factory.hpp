#ifndef READER_FACTORY_HPP
#define READER_FACTORY_HPP

#include <memory>

#include "ireader.hpp"
#include "supported_input_formats.hpp"

namespace Converter {

/**
 * @brief Creates reader objects for mesh reading.
 */
class ReaderFactory {
public:
  /**
   * @brief Creates the reader based on the input format.
   * @param format The format corresponding to the reader object that should be
   * created.
   */
  [[nodiscard]] static std::unique_ptr<IReader>
  createReader(Reader::InputFormat format);
};

} // namespace Converter

#endif