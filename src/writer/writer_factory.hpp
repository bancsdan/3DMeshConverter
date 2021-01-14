#ifndef WRITER_FACTORY_HPP
#define WRITER_FACTORY_HPP

#include <memory>

#include "supported_output_formats.hpp"
#include "iwriter.hpp"

class WriterFactory
{
public:
    [[nodiscard]]
    static std::unique_ptr<IWriter> createWriter(Writer::OutputFormat format);
};

#endif