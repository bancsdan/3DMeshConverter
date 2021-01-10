#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <fstream>

#include "ireader.hpp"

class ObjReader final : public IReader
{
public:
    MeshData read(std::ifstream& in_file) final override;
};

#endif