#include <memory>

#include "reader_factory.hpp"
#include "ireader.hpp"
#include "obj_reader.hpp"
#include "supported_input_formats.hpp"

std::unique_ptr<IReader> ReaderFactory::createReader(InputFormat format)
{
    switch (format)
        {
        case InputFormat::OBJ:
                return std::unique_ptr<ObjReader>(new ObjReader());
                break;        
        default:
                return std::unique_ptr<IReader>(nullptr);
                break;
        }
}