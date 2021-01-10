#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <fstream>

#include "ireader.hpp"

class ObjReader final : public IReader
{
public:
    ~ObjReader() = default;
    MeshData read(const std::string& in_file) final override;
};

#endif