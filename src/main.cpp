#include <iostream>
#include <fstream>
#include <string>
#include <array>

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

    const auto input_extension = Reader::convertInputFormatToEnum(input_filename.substr(input_filename.find_last_of('.') + 1));
    const auto output_extension = Writer::convertOutputFormatToEnum(output_filename.substr(output_filename.find_last_of('.') + 1));

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

    std::ifstream in_file;
    in_file.open(input_filename);
    if (!in_file)
    {
        std::cerr << "ERROR: Input file not found." << std::endl;
        return 1;
    }
    
    auto reader = ReaderFactory::createReader(input_extension);
    MeshData mesh = (*reader).read(in_file);

	return 0;
}