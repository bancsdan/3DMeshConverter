#include "exception.hpp"

const char* FileNotFoundException::what() const
{
        return "File not found.";
}
