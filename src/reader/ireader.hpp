#ifndef IREADER_HPP
#define IREADER_HPP

#include <fstream>

struct MeshData;

class IReader
{
public:
    virtual ~IReader() = 0;
    virtual MeshData read(std::ifstream& in_file) = 0;
};

#endif