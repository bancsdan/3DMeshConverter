#include <cstring>
#include <string>

#include "exception.hpp"

const char* FileNotFoundException::what() const noexcept { return "File not found."; }

const char* IllFormedFileException::what() const noexcept {
  return "Ill formed file, cannot read contents.";
}