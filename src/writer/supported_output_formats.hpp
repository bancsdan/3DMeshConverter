#ifndef SUPPORTED_OUTPUT_FORMATS_HPP
#define SUPPORTED_OUTPUT_FORMATS_HPP

#include <array>
#include <string>
#include <utility>

namespace Converter {
namespace Writer {

enum class OutputFormat { STL, INVALID };

static constexpr std::array<std::pair<const char*, OutputFormat>, 1>
    supported_output_formats_map{std::make_pair(".stl", OutputFormat::STL)};

OutputFormat convertOutputFormatToEnum(const std::string& format);
bool isSupportedOutputFormat(OutputFormat format);

}  // namespace Writer
}  // namespace Converter

#endif