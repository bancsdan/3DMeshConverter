#include <Eigen/Dense>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

#include "geometry/meshdata.hpp"
#include "stl_writer.hpp"
#include "utility.hpp"

void StlWriter::write(const std::string& file_name,
                      const MeshData& mesh) const {
  std::ofstream out_file;
  out_file.open(file_name, std::ios_base::binary);

  writeHeader(out_file);
  writeNumOfTriangles(out_file, mesh);
  writeTriangles(out_file, mesh);
}

void StlWriter::writeHeader(std::ofstream& out_file) const {
  std::array<char, c_header_size_in_bytes> header_buffer;
  header_buffer.fill(static_cast<char>(0));

  out_file.write(header_buffer.data(), c_header_size_in_bytes);
}

void StlWriter::writeNumOfTriangles(std::ofstream& out_file,
                                    const MeshData& mesh) const {
  std::uint32_t number_of_triangles =
      static_cast<std::uint32_t>(mesh.m_triangles.size());

  if (!Utility::isIntegerLittleEndian()) {
    Utility::swapByteOrder(number_of_triangles);
  }

  out_file.write((const char*)(&number_of_triangles), sizeof(std::uint32_t));
}

void StlWriter::writeTriangles(std::ofstream& out_file,
                               const MeshData& mesh) const {
  const bool needs_byte_swap = !Utility::isFloatLittleEndian();

  if (needs_byte_swap) {
    for (const auto& triangle : mesh.m_triangles) {
      const auto& a_pos = triangle.m_a.m_pos.cast<float>();
      const auto& b_pos = triangle.m_b.m_pos.cast<float>();
      const auto& c_pos = triangle.m_c.m_pos.cast<float>();

      std::array<float, 9U> triangle_coords;
      triangle_coords[0U] = Utility::swapByteOrder(a_pos.x());
      triangle_coords[1U] = Utility::swapByteOrder(a_pos.y());
      triangle_coords[2U] = Utility::swapByteOrder(a_pos.z());
      triangle_coords[3U] = Utility::swapByteOrder(b_pos.x());
      triangle_coords[4U] = Utility::swapByteOrder(b_pos.y());
      triangle_coords[5U] = Utility::swapByteOrder(b_pos.z());
      triangle_coords[6U] = Utility::swapByteOrder(c_pos.x());
      triangle_coords[7U] = Utility::swapByteOrder(c_pos.y());
      triangle_coords[8U] = Utility::swapByteOrder(c_pos.z());

      Eigen::Vector4f cross =
          (triangle.m_b.m_pos - triangle.m_a.m_pos)
              .cross3(triangle.m_c.m_pos - triangle.m_a.m_pos)
              .cast<float>();
      cross.normalize();

      cross.x() = Utility::swapByteOrder(cross.x());
      cross.y() = Utility::swapByteOrder(cross.y());
      cross.z() = Utility::swapByteOrder(cross.z());

      out_file.write((const char*)&(cross.x()), sizeof(float));
      out_file.write((const char*)&(cross.y()), sizeof(float));
      out_file.write((const char*)&(cross.z()), sizeof(float));
      out_file.write((const char*)triangle_coords.data(),
                     triangle_coords.size() * sizeof(float));

      static constexpr std::uint16_t attribute_byte_count = 0U;
      out_file.write((const char*)&attribute_byte_count, sizeof(std::uint16_t));
    }
  } else {
    for (const auto& triangle : mesh.m_triangles) {
      const auto& a_pos = triangle.m_a.m_pos.cast<float>();
      const auto& b_pos = triangle.m_b.m_pos.cast<float>();
      const auto& c_pos = triangle.m_c.m_pos.cast<float>();

      std::array<float, 9U> triangle_coords;
      triangle_coords[0U] = a_pos.x();
      triangle_coords[1U] = a_pos.y();
      triangle_coords[2U] = a_pos.z();
      triangle_coords[3U] = b_pos.x();
      triangle_coords[4U] = b_pos.y();
      triangle_coords[5U] = b_pos.z();
      triangle_coords[6U] = c_pos.x();
      triangle_coords[7U] = c_pos.y();
      triangle_coords[8U] = c_pos.z();

      Eigen::Vector4f cross =
          (b_pos - a_pos).cross3(c_pos - a_pos).cast<float>();
      cross.normalize();

      out_file.write((const char*)&(cross.x()), sizeof(float));
      out_file.write((const char*)&(cross.y()), sizeof(float));
      out_file.write((const char*)&(cross.z()), sizeof(float));
      out_file.write((const char*)triangle_coords.data(),
                     triangle_coords.size() * sizeof(float));

      static constexpr std::uint16_t attribute_byte_count = 0U;
      out_file.write((const char*)&attribute_byte_count, sizeof(std::uint16_t));
    }
  }
}