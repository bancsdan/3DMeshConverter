#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "converter/reader/ireader.hpp"
#include "geometry/triangle.hpp"
#include "utility.hpp"

int main(int argc, char* argv[])
{
    if ( argc != 3 )
    {
        Utility::displayHelp(argv);
        return 1;
    }

    const std::string input_filename{argv[1]};
    const std::string output_filename{argv[2]};

    std::ifstream in_file;
    in_file.open(input_filename);
    if (!in_file)
    {
        std::cerr << "ERROR: Input file not found." << std::endl;
        return 1;
    }

    const auto input_extension = Utility::convertInputFormatToEnum(input_filename.substr(input_filename.find_last_of('.') + 1));
    const auto output_extension = Utility::convertOutputFormatToEnum(output_filename.substr(output_filename.find_last_of('.') + 1));

    if (!Utility::isSupportedInputFormat(input_extension))
    {
        std::cerr << "ERROR: Input file format not supported." << std::endl;
        return 1;
    }

    if (!Utility::isSupportedOutputFormat(output_extension))
    {
        std::cerr << "ERROR: Output file format not supported." << std::endl;
        return 1;
    }
    
    auto reader = Utility::getFormatReader(input_extension);

	return 0;
}