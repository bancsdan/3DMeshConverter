#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "geometry/triangle.hpp"
#include "utility.hpp"

int main(int argc, char* argv[])
{
    if ( argc != 3 )
    {
        Utility::displayHelp(argc, argv);
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

    const std::string input_extension = input_filename.substr(input_filename.find_last_of('.') + 1);
    const std::string output_extension = output_filename.substr(input_filename.find_last_of('.') + 1);


    std::cout << input_extension;

	return 0;
}