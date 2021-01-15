#include <algorithm>

#include "supported_output_formats.hpp"

Writer::OutputFormat Writer::convertOutputFormatToEnum(
    const std::string& format) {
  auto entry = std::find_if(supported_output_formats_map.begin(),
                            supported_output_formats_map.end(),
                            [&format](const auto& format_pair) {
                              return format_pair.first == format;
                            });
  if (entry != supported_output_formats_map.end()) {
    return entry->second;
  }
  return OutputFormat::INVALID;
}

bool Writer::isSupportedOutputFormat(OutputFormat format) {
  return format != OutputFormat::INVALID;
}