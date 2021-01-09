#include <iostream>

#include "geometry/triangle.hpp"

void displayHelp(int argc, char* argv[])
{
        std::cout << "Usage: "<< argv[0] <<" <inputfile> <outputfile>" << std::endl << std::endl;
        std::cout << "Currently supported input filetypes:" << std::endl;
        std::cout << "\t.obj" << std::endl << std::endl;
        std::cout << "Currently supported output filetypes:" << std::endl;
        std::cout << "\t.stl binary" << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
    if ( argc != 3 )
    {
        displayHelp(argc, argv);
    }

	return 0;
}