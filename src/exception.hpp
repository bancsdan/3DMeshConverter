
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class FileNotFoundException final : public std::exception {
 public:
  const char* what() const final override;
};

class IllFormedFileException final : public std::exception {
 public:
  const char* what() const final override;
};

#endif