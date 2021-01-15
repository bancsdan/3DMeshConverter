#include <math.h>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

#include "reader/supported_input_formats.hpp"
#include "utility.hpp"
#include "writer/supported_output_formats.hpp"

void Utility::displayHelp(char* argv[]) {
  std::cout << "Usage: " << argv[0] << " <inputfile> <outputfile>" << std::endl
            << std::endl;

  std::cout << "Currently supported input filetypes:" << std::endl;
  for (const auto& format_pair : Reader::supported_input_formats_map) {
    std::cout << "\t." << format_pair.first << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Currently supported output filetypes:" << std::endl;
  for (const auto format_pair : Writer::supported_output_formats_map) {
    std::cout << "\t." << format_pair.first << std::endl;
  }
  std::cout << std::endl;
}

std::string Utility::toLower(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](std::string::value_type c) {
                   return static_cast<std::string::value_type>(std::tolower(c));
                 });
  return str;
}

std::vector<std::string> Utility::splitString(const std::string& str,
                                              std::string::value_type delim) {
  std::vector<std::string> result;
  std::istringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delim)) {
    result.push_back(token);
  }

  return result;
}

std::vector<std::string> Utility::splitString(const std::string& str) {
  std::istringstream buffer(str);
  std::vector<std::string> result{std::istream_iterator<std::string>(buffer),
                                  std::istream_iterator<std::string>()};
  return result;
}

bool Utility::startsWith(const std::string& str, const char* start) {
  return str.rfind(start, 0) == 0;
}
