#include <Eigen/Dense>
#include <array>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

#include "geometry/meshdata.hpp"
#include "stl_writer.hpp"
#include "utility.hpp"

namespace Converter {

void StlWriter::write(std::ostream &out_file, const MeshData &mesh) const {
  writeHeader(out_file);
  writeNumOfTriangles(out_file, mesh);
  writeTriangles(out_file, mesh);
}

void StlWriter::writeHeader(std::ostream &out_file) const {
  std::array<char, c_header_size_in_bytes> header_buffer;
  header_buffer.fill(static_cast<char>(0));

  out_file.write(header_buffer.data(), c_header_size_in_bytes);
}

void StlWriter::writeNumOfTriangles(std::ostream &out_file,
                                    const MeshData &mesh) const {
  std::uint32_t number_of_triangles =
      static_cast<std::uint32_t>(mesh.triangles.size());

  if (!Utility::isIntegerLittleEndian()) {
    Utility::swapByteOrder(number_of_triangles);
  }

  out_file.write((const char *)(&number_of_triangles), sizeof(std::uint32_t));
}

void StlWriter::writeTriangles(std::ostream &out_file,
                               const MeshData &mesh) const {
  const bool needs_byte_swap = !Utility::isFloatLittleEndian();

  const std::function<float(const float &)> swap_byte_order =
      Utility::swapByteOrder<float>;
  const std::function<float(const float &)> do_nothing =
      [](const float &arg) -> float { return arg; };
  const auto swapper_func = needs_byte_swap ? swap_byte_order : do_nothing;

  for (const auto &triangle : mesh.triangles) {
    const auto &a_pos = triangle.a.pos.cast<float>();
    const auto &b_pos = triangle.b.pos.cast<float>();
    const auto &c_pos = triangle.c.pos.cast<float>();

    std::array<float, 9U> triangle_coords;
    triangle_coords[0U] = swapper_func(a_pos.x());
    triangle_coords[1U] = swapper_func(a_pos.y());
    triangle_coords[2U] = swapper_func(a_pos.z());
    triangle_coords[3U] = swapper_func(b_pos.x());
    triangle_coords[4U] = swapper_func(b_pos.y());
    triangle_coords[5U] = swapper_func(b_pos.z());
    triangle_coords[6U] = swapper_func(c_pos.x());
    triangle_coords[7U] = swapper_func(c_pos.y());
    triangle_coords[8U] = swapper_func(c_pos.z());

    Eigen::Vector4f cross = (triangle.b.pos - triangle.a.pos)
                                .cross3(triangle.c.pos - triangle.a.pos)
                                .cast<float>();
    cross.normalize();

    cross.x() = swapper_func(cross.x());
    cross.y() = swapper_func(cross.y());
    cross.z() = swapper_func(cross.z());

    out_file.write((const char *)&(cross.x()), sizeof(float));
    out_file.write((const char *)&(cross.y()), sizeof(float));
    out_file.write((const char *)&(cross.z()), sizeof(float));
    out_file.write((const char *)triangle_coords.data(),
                   triangle_coords.size() * sizeof(float));

    static constexpr std::uint16_t attribute_byte_count = 0U;
    out_file.write((const char *)&attribute_byte_count, sizeof(std::uint16_t));
  }
}
} // namespace Converter