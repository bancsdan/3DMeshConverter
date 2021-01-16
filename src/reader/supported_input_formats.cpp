#include <algorithm>

#include "supported_input_formats.hpp"

namespace Converter {

Reader::InputFormat Reader::convertInputFormatToEnum(
    const std::string& format) {
  const auto predicate = [&format](const auto& format_pair) {
    return format_pair.first == format;
  };

  if (const auto it =
          std::find_if(supported_input_formats_map.begin(),
                       supported_input_formats_map.end(), predicate);
      it != supported_input_formats_map.end()) {
    return it->second;
  }
  return InputFormat::INVALID;
}

bool Reader::isSupportedInputFormat(InputFormat format) {
  return format != InputFormat::INVALID;
}

}  // namespace Converter