#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>

class IReader;
class IWriter;

class Converter
{
public:
    void Convert(const IReader& reader, const std::string& readfilename, const IWriter& writer, const std::string& writefilename) const noexcept;

};

#endif