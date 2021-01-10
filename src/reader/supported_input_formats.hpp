#ifndef SUPPORTED_INPUT_FORMATS_HPP
#define SUPPORTED_INPUT_FORMATS_HPP

#include <array>
#include <utility>

enum class InputFormat {
    OBJ,
    INVALID
};

static constexpr std::array<std::pair<const char*, InputFormat>, 1> input_formats {
    std::make_pair("obj", InputFormat::OBJ)
};

#endif