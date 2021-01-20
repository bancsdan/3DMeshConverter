#include <Eigen/Dense>
#include <array>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
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
  std::array<double, 3U> scale_args;
  app.add_option(
      "--scale", scale_args,
      "Specifies the (x,y,z) scale of the scaling. Default is (1,1,1).");
  std::array<double, 4U> rotation_args;
  app.add_option("--rotate", rotation_args,
                 "Specifies the (x,y,z,angle) axis of the rotation and the "
                 "angle in radians.");
  std::array<double, 3U> translation_args;
  app.add_option("--translate", translation_args,
                 "Specifies the (x,y,z) amount of the translation.");
  std::array<double, 3U> is_point_inside_args;
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

  const bool scale_set = app.count("--scale") > 0U;
  const bool rotation_set = app.count("--rotate") > 0U;
  const bool translation_set = app.count("--translate") > 0U;
  const bool is_point_inside_set = app.count("--is_point_inside") > 0U;

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
      std::ifstream in_file_stream;
      in_file_stream.open(input_filename);
      if (!in_file_stream) {
        throw FileNotFoundException();
      }
      mesh = reader->read(in_file_stream);
    }

    if (scale_set || rotation_set || translation_set) {
      Eigen::Matrix4d scale_matrix;
      scale_matrix.setIdentity();
      if (scale_set) {
        scale_matrix = Utility::getScaleMatrix(
            {scale_args[0U], scale_args[1U], scale_args[2U]});
      }

      Eigen::Matrix4d rotation_matrix;
      rotation_matrix.setIdentity();
      if (rotation_set) {
        rotation_matrix = Utility::getRotationMatrix(
            {rotation_args[0U], rotation_args[1U], rotation_args[2U]},
            rotation_args[3U]);
      }

      Eigen::Matrix4d translation_matrix;
      translation_matrix.setIdentity();
      if (translation_set) {
        translation_matrix = Utility::getTranslationMatrix(
            {translation_args[0U], translation_args[1U], translation_args[2U]});
      }

      mesh.transform(translation_matrix, rotation_matrix, scale_matrix);
    }

    std::cout << std::setprecision(std::numeric_limits<double>::digits10)
              << "Area: " << mesh.calculateSurfaceArea() << std::endl;
    std::cout << std::setprecision(std::numeric_limits<double>::digits10)
              << "Volume: " << mesh.calculateVolume() << std::endl;

    if (is_point_inside_set) {
      const bool is_inside = mesh.isPointInside(
          {is_point_inside_args[0U], is_point_inside_args[1U],
           is_point_inside_args[2U], 1.0});
      std::cout << "Point is" << (is_inside ? "" : " not")
                << " inside the mesh." << std::endl;
    }

    auto writer = WriterFactory::createWriter(output_extension_enum);
    if (writer) {
      std::ofstream out_file;
      out_file.open(output_filename, std::ios_base::binary);
      writer->write(out_file, mesh);
    }
  } catch (const UnsupportedFormatException &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    Utility::displaySupportedFormats();
    return -1;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return -1;
  }
  return 0;
}