#ifndef SUPPORTED_INPUT_FORMATS_HPP
#define SUPPORTED_INPUT_FORMATS_HPP

#include <array>
#include <string>
#include <utility>

namespace Converter {
namespace Reader {

/**
 * @brief The enum containing the supported input formats
 * in enum form.
 */
enum class InputFormat { OBJ, INVALID };

/**
 * @brief Basically a constexpr map, mapping the extensions to
 * the corresponding enums.
 */
static constexpr std::array<std::pair<const char *, InputFormat>, 1>
    supported_input_formats_map{std::make_pair(".obj", InputFormat::OBJ)};

/**
 * @brief Converts the input extension string to a corresponding enum.
 * @param format The string containing the extension of the file.
 * @return The enum corresponding to the extension format, if there is
 * no such format, returns invalid.
 */
InputFormat convertInputFormatToEnum(const std::string &format);

} // namespace Reader
} // namespace Converter

#endif