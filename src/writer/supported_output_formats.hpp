#ifndef SUPPORTED_OUTPUT_FORMATS_HPP
#define SUPPORTED_OUTPUT_FORMATS_HPP

#include <array>
#include <string>
#include <utility>

namespace Converter {
namespace Writer {

/**
 * @brief The enum containing the supported output formats
 * in enum form.
 */
enum class OutputFormat { STL, INVALID };

/**
 * @brief Basically a constexpr map, mapping the extensions to
 * the corresponding enums.
 */
static constexpr std::array<std::pair<const char *, OutputFormat>, 1>
    supported_output_formats_map{std::make_pair(".stl", OutputFormat::STL)};

/**
 * @brief Converts the output extension string to a corresponding enum.
 * @param format The string containing the extension of the file.
 * @return The enum corresponding to the extension format, if there is
 * no such format, returns invalid.
 */
OutputFormat convertOutputFormatToEnum(const std::string &format);

} // namespace Writer
} // namespace Converter

#endif