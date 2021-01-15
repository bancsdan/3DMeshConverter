#ifndef IWRITER_HPP
#define IWRITER_HPP

#include <string>

struct MeshData;

class IWriter {
 public:
  virtual ~IWriter() = default;
  virtual void write(const std::string& file_name,
                     const MeshData& mesh) const = 0;
};

#endif