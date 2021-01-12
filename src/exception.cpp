#include "exception.hpp"

const char* FileNotFoundException::what() const
{
        return "File not found.";
}

const char* IllFormedFileException::what() const
{
        return "Ill formed file, cannot read contents.";
}