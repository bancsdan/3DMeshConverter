#ifndef SUPPORTED_INPUT_FORMATS_HPP
#define SUPPORTED_INPUT_FORMATS_HPP

#include <array>
#include <string>
#include <utility>

namespace Reader {
enum class InputFormat { OBJ, INVALID };

static constexpr std::array<std::pair<const char*, InputFormat>, 1>
    supported_input_formats_map{std::make_pair(".obj", InputFormat::OBJ)};

InputFormat convertInputFormatToEnum(const std::string& format);
bool isSupportedInputFormat(InputFormat format);
}  // namespace Reader

#endif