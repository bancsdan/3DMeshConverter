#include <array>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "reader/reader_factory.hpp"
#include "reader/supported_input_formats.hpp"
#include "utility.hpp"
#include "writer/supported_output_formats.hpp"
#include "writer/writer_factory.hpp"

int main(int argc, char *argv[]) {
  using namespace Converter;

  if (argc != 3) {
    Utility::displayHelp(argv);
    return -1;
  }

  if constexpr (!std::numeric_limits<float>::is_iec559 || sizeof(float) != 4U) {
    std::cerr << "ERROR: The implementation doesn't support the IEEE 754 - IEC "
                 "559 standard for float type."
              << std::endl;
    return -1;
  }

  const std::string input_filename{argv[1]};
  const std::string output_filename{argv[2]};

  auto input_extension = Utility::toLower(
      std::filesystem::path(input_filename).extension().string());
  auto output_extension = Utility::toLower(
      std::filesystem::path(output_filename).extension().string());

  const auto input_extension_enum =
      Reader::convertInputFormatToEnum(input_extension);
  const auto output_extension_enum =
      Writer::convertOutputFormatToEnum(output_extension);

  if (input_extension_enum == Reader::InputFormat::INVALID) {
    std::cerr << "ERROR: Input file format not supported." << std::endl;
    return -1;
  }

  if (output_extension_enum == Writer::OutputFormat::INVALID) {
    std::cerr << "ERROR: Output file format not supported." << std::endl;
    return -1;
  }

  auto reader = ReaderFactory::createReader(input_extension_enum);

  MeshData mesh;
  try {
    if (reader) {
      mesh = reader->read(input_filename);
    }
  } catch (const std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return -1;
  }

  
  const auto& scale_matrix = Utility::getScaleMatrix({1.0, 2.0, 1.0});
  const auto& rotation_matrix = Utility::getRotationMatrix({0.0, 0.0, 0.0}, 0.0);
  const auto& translation_matrix = Utility::getTranslationMatrix({0.0, 0.0, 0.0});
  Utility::transformMesh(mesh, translation_matrix, rotation_matrix, scale_matrix);

  std::cout << std::setprecision(std::numeric_limits<double>::digits10)
            << "Area: " << Utility::calculateMeshSurfaceArea(mesh) << std::endl;

  std::cout << std::setprecision(std::numeric_limits<double>::digits10)
            << "Volume: " << Utility::calculateMeshVolume(mesh) << std::endl;
  
  auto writer = WriterFactory::createWriter(output_extension_enum);
  try {
    if (writer) {
      writer->write(output_filename, mesh);
    }
  } catch (const std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}