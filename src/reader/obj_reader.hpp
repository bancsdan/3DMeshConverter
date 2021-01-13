#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <Eigen/Dense>

#include "ireader.hpp"

struct MeshData;

class ObjReader final : public IReader
{
    static constexpr char* f = "f";
    static constexpr char* v = "v";
    static constexpr char* vn = "vn";
    static constexpr char* vt = "vt";

    void readFace(const std::vector<std::string>& line,
        const std::vector<Eigen::Vector4d>& vertices,
        const std::vector<Eigen::Vector4d>& vertex_textures,
        const std::vector<Eigen::Vector4d>& vertex_normals,
        MeshData& mesh) const;
    void readVector(const std::vector<std::string>& line, std::vector<Eigen::Vector4d>& vectors) const;
public:
    ~ObjReader() = default;
    MeshData read(const std::string& in_file) final override;
};

#endif