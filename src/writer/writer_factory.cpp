#include <memory>

#include "iwriter.hpp"
#include "stl_writer.hpp"
#include "supported_output_formats.hpp"
#include "writer_factory.hpp"

namespace Converter {

std::unique_ptr<IWriter>
WriterFactory::createWriter(Writer::OutputFormat format) {
  switch (format) {
  case Writer::OutputFormat::STL:
    return std::make_unique<StlWriter>();
    break;
  default:
    return nullptr;
    break;
  }
}

} // namespace Converter