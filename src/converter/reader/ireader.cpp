#include <memory>

#include "ireader.hpp"
#include "obj_reader.hpp"
#include "utility.hpp"

std::unique_ptr<IReader> IReader::createReader(Utility::InputFormat format)
{
    switch (format)
        {
        case Utility::InputFormat::OBJ:
                return std::unique_ptr<ObjReader>(new ObjReader);
                break;        
        default:
                return std::unique_ptr<IReader>(nullptr);
                break;
        }
}