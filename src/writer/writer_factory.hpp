#ifndef WRITER_FACTORY_HPP
#define WRITER_FACTORY_HPP

#include <memory>

#include "iwriter.hpp"
#include "supported_output_formats.hpp"

namespace Converter {

class WriterFactory {
public:
  [[nodiscard]] static std::unique_ptr<IWriter>
  createWriter(Writer::OutputFormat format);
};

} // namespace Converter
#endif