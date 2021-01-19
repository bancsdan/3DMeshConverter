#include <cstring>
#include <string>

#include "exception.hpp"

const char *FileNotFoundException::what() const noexcept {
  return "File not found.";
}

const char *IllFormedFileException::what() const noexcept {
  return "Ill formed file, cannot read contents.";
}

const char *UnsupportedInputFormatException::what() const noexcept {
  return "Unsupported input file format.";
}

const char *UnsupportedOutputFormatException::what() const noexcept {
  return "Unsupported output file format.";
}