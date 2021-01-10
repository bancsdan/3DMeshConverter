
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

class FileNotFoundException : public std::exception
{
  virtual const char* what() const override;
};

#endif