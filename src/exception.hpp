
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

class FileNotFoundException final : public std::exception
{
  const char* what() const final override;
};

#endif