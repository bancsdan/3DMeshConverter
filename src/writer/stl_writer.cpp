#include <fstream>
#include <iostream>
#include <array>
#include <sstream>
#include <cstdint>

#include "stl_writer.hpp"
#include "utility.hpp"
#include "geometry/meshdata.hpp"

void StlWriter::write(const std::string& file_name, const MeshData& mesh) const
{
    std::ofstream out_file;
    out_file.open(file_name);

    writeHeader(out_file);
    writeNumOfTriangles(out_file, mesh);
    writeTriangles(out_file, mesh);
}

void StlWriter::writeHeader(std::ofstream& out_file) const
{
    std::array<char, c_header_size_in_bytes> header_buffer;
    header_buffer.fill(static_cast<char>(0));

    out_file.write(header_buffer.data(), c_header_size_in_bytes);
}

void StlWriter::writeNumOfTriangles(std::ofstream& out_file, const MeshData& mesh) const
{
    std::uint32_t number_of_triangles = static_cast<std::uint32_t>(mesh.m_triangles.size());

    if (!Utility::isIntegerLittleEndian())
    {
        Utility::swapByteOrder(number_of_triangles);
    }

    out_file.write((const char*)(&number_of_triangles), sizeof(std::uint32_t));
}

void StlWriter::writeTriangles(std::ofstream& out_file, const MeshData& mesh) const
{
    const bool needs_byte_swap = !Utility::isFloatLittleEndian();

    if (needs_byte_swap)
    {

    }
    else
    {
        for (const auto& triangle : mesh.m_triangles)
        {

        }
    }
    
}