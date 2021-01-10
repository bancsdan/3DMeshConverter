#ifndef READER_FACTORY_HPP
#define READER_FACTORY_HPP

#include <memory>

#include "supported_input_formats.hpp"
#include "ireader.hpp"

class ReaderFactory
{
public:
    [[nodiscard]]
    static std::unique_ptr<IReader> createReader(Reader::InputFormat format);
};

#endif