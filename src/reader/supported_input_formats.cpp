#include "supported_input_formats.hpp"

Reader::InputFormat Reader::convertInputFormatToEnum(
    const std::string& format) {
  auto entry = std::find_if(supported_input_formats_map.begin(),
                            supported_input_formats_map.end(),
                            [&format](const auto& format_pair) {
                              return format_pair.first == format;
                            });
  if (entry != supported_input_formats_map.end()) {
    return entry->second;
  }
  return InputFormat::INVALID;
}

bool Reader::isSupportedInputFormat(InputFormat format) {
  return format != InputFormat::INVALID;
}