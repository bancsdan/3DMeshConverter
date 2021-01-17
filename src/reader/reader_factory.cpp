#include <memory>

#include "ireader.hpp"
#include "obj_reader.hpp"
#include "reader_factory.hpp"
#include "supported_input_formats.hpp"

namespace Converter {

std::unique_ptr<IReader>
ReaderFactory::createReader(Reader::InputFormat format) {
  switch (format) {
  case Reader::InputFormat::OBJ:
    return std::make_unique<ObjReader>();
    break;
  default:
    return nullptr;
    break;
  }
}

} // namespace Converter