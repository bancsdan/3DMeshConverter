#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <filesystem>

#include "utility.hpp"
#include "reader/reader_factory.hpp"
#include "reader/supported_input_formats.hpp"
#include "writer/supported_output_formats.hpp"
#include "geometry/triangle.hpp"
#include "geometry/meshdata.hpp"

int main(int argc, char* argv[])
{
    if ( argc != 3 )
    {
        Utility::displayHelp(argv);
        return 1;
    }

    const std::string input_filename{argv[1]};
    const std::string output_filename{argv[2]};

    const auto input_extension = Reader::convertInputFormatToEnum(std::filesystem::path(input_filename).extension().string());
    const auto output_extension = Writer::convertOutputFormatToEnum(std::filesystem::path(output_filename).extension().string());

    if (!Reader::isSupportedInputFormat(input_extension))
    {
        std::cerr << "ERROR: Input file format not supported." << std::endl;
        return 1;
    }

    if (!Writer::isSupportedOutputFormat(output_extension))
    {
        std::cerr << "ERROR: Output file format not supported." << std::endl;
        return 1;
    }
    
    auto reader = ReaderFactory::createReader(input_extension);

    try
    {
        MeshData mesh = reader->read(input_filename);
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    

	return 0;
}