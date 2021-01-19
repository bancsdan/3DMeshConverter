
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class FileNotFoundException final : public std::exception {
public:
  const char *what() const noexcept;
};

class IllFormedFileException final : public std::exception {
public:
  const char *what() const noexcept;
};

class UnsupportedFormatException : public std::exception {
};

class UnsupportedInputFormatException final : public UnsupportedFormatException {
public:
  const char *what() const noexcept;
};

class UnsupportedOutputFormatException final : public UnsupportedFormatException {
public:
  const char *what() const noexcept;
};

#endif