#include <array>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "CLI11.hpp"
#include "exception.hpp"
#include "geometry/meshdata.hpp"
#include "geometry/triangle.hpp"
#include "reader/reader_factory.hpp"
#include "utility.hpp"
#include "writer/writer_factory.hpp"

using namespace Converter;

int main(int argc, char *argv[]) {

  if constexpr (!std::numeric_limits<float>::is_iec559 || sizeof(float) != 4U) {
    std::cerr << "ERROR: The implementation doesn't support the IEEE 754 - IEC "
                 "559 standard for float type."
              << std::endl;
    return -1;
  }

  CLI::App app{"A 3D model file converter."};
  std::array<double, 3> scale_args;
  app.add_option(
      "--scale", scale_args,
      "Specifies the (x,y,z) scale of the scaling. Default is (1,1,1).");
  std::array<double, 4> rotation_args;
  app.add_option("--rotate", rotation_args,
                 "Specifies the (x,y,z,angle) axis of the rotation and the "
                 "angle in radians.");
  std::array<double, 3> translation_args;
  app.add_option("--translate", translation_args,
                 "Specifies the (x,y,z) amount of the translation.");
  std::array<double, 3> is_point_inside_args;
  app.add_option("--is_point_inside", is_point_inside_args,
                 "Specifies the (x,y,z) coordinates of the point you wish to "
                 "know if it is inside the mesh or not.");
  std::string input_filename;
  app.add_option("--input", input_filename, "The path to the input file.")
      ->required();
  std::string output_filename;
  app.add_option("--output", output_filename, "The path to the output file.")
      ->required();
  CLI11_PARSE(app, argc, argv);

  try {
    auto input_extension = Utility::toLower(
        std::filesystem::path(input_filename).extension().string());
    auto output_extension = Utility::toLower(
        std::filesystem::path(output_filename).extension().string());

    const auto input_extension_enum =
        Reader::convertInputFormatToEnum(input_extension);
    const auto output_extension_enum =
        Writer::convertOutputFormatToEnum(output_extension);

    if (input_extension_enum == Reader::InputFormat::INVALID) {
      throw UnsupportedInputFormatException();
    }

    if (output_extension_enum == Writer::OutputFormat::INVALID) {
      throw UnsupportedOutputFormatException();
    }

    auto reader = ReaderFactory::createReader(input_extension_enum);
    MeshData mesh;
    if (reader) {
      mesh = reader->read(input_filename);
    }

    std::cout << std::setprecision(std::numeric_limits<double>::digits10)
              << "Area: " << Utility::calculateMeshSurfaceArea(mesh)
              << std::endl;
    std::cout << std::setprecision(std::numeric_limits<double>::digits10)
              << "Volume: " << Utility::calculateMeshVolume(mesh) << std::endl;

    auto writer = WriterFactory::createWriter(output_extension_enum);

    if (writer) {
      writer->write(output_filename, mesh);
    }
  } catch (const UnsupportedFormatException &e)  {
    std::cerr << "ERROR: " << e.what() << std::endl;
    Utility::displaySupportedFormats();
    return -1;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return -1;
  }
  return 0;
}