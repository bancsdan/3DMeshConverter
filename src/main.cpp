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

    auto input_extension = Utility::toLower(std::filesystem::path(input_filename).extension().string());
    auto output_extension = Utility::toLower(std::filesystem::path(output_filename).extension().string());

    const auto input_extension_enum = Reader::convertInputFormatToEnum(input_extension);
    const auto output_extension_enum = Writer::convertOutputFormatToEnum(output_extension);

    if (!Reader::isSupportedInputFormat(input_extension_enum))
    {
        std::cerr << "ERROR: Input file format not supported." << std::endl;
        return 1;
    }

    if (!Writer::isSupportedOutputFormat(output_extension_enum))
    {
        std::cerr << "ERROR: Output file format not supported." << std::endl;
        return 1;
    }
    
    auto reader = ReaderFactory::createReader(input_extension_enum);

    try
    {
        if(reader)
        {
            MeshData mesh = reader->read(input_filename);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    //ApplyTranformation(mesh, tranfrom);

    /*
    try
    {
        MeshData mesh = Writer->write(output_filename, mesh);
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    */

	return 0;
}