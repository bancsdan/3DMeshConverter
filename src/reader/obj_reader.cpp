#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>

#include "obj_reader.hpp"
#include "geometry/meshdata.hpp"
#include "exception.hpp"
#include "utility.hpp"

MeshData ObjReader::read(const std::string& file_name)
{
    std::ifstream in_file_stream;
    in_file_stream.open(file_name);
    if (!in_file_stream)
    {
        throw FileNotFoundException();
    }

    MeshData result;
    std::vector<Eigen::Vector4d> vertices;
    std::vector<Eigen::Vector4d> vertex_normals;
    std::vector<Eigen::Vector4d> vertex_textures;

    for (std::string line; std::getline(in_file_stream, line); )
    {
        const auto lineVect = Utility::splitString(line, ' ');

        if (!lineVect.empty())
        {
            if (Utility::startsWith(lineVect[0], c_vn))
            {
                readVector(lineVect, vertex_normals);
            }
            else if (Utility::startsWith(lineVect[0], c_vt))
            {
                readVector(lineVect, vertex_textures);
            }
            else if (Utility::startsWith(lineVect[0], c_v))
            {
                readVector(lineVect, vertices);
            }
            else if(Utility::startsWith(lineVect[0], c_f))
            {
                readFace(lineVect, vertices, vertex_textures, vertex_normals, result);
            }            
            else if (Utility::startsWith(lineVect[0], c_mtllib))
            {
                if (lineVect.size() > 1)
                {
                    result.m_material_file = lineVect[1];
                }
            }
        }

    }

    return result;
}

void ObjReader::readVector(const std::vector<std::string>& line, std::vector<Eigen::Vector4d>& vectors) const
{
    if (line.size() != 4 && line.size() != 5)
    {
        throw IllFormedFileException();
    }

    Eigen::Vector4d vec{0.0, 0.0, 0.0, 0.0};
    unsigned int index = 0;
    for (auto it = line.begin() + 1; it != line.end(); ++it)
    {
        vec[index++] = std::stod(*it);
    }

    vectors.push_back(vec);
}

void ObjReader::readFace(const std::vector<std::string>& line,
    const std::vector<Eigen::Vector4d>& vertices,
    const std::vector<Eigen::Vector4d>& vertex_textures,
    const std::vector<Eigen::Vector4d>& vertex_normals,
    MeshData& mesh) const
{
    if (line.size() < 4)
    {
        throw IllFormedFileException();
    }

    std::vector<const Eigen::Vector4d*> face_vertices;
    std::vector<const Eigen::Vector4d*> face_vertex_textures;
    std::vector<const Eigen::Vector4d*> face_vertex_normals;
    for (auto it = line.begin() + 1; it != line.end(); ++it)
    {
        const auto face_vertex_str = Utility::splitString(*it, '/');
        if (face_vertex_str.size() == 3)
        {
            face_vertices.push_back(&vertices[std::stoi(face_vertex_str[0]) - 1] );
            if (!face_vertex_str[1].empty())
            {
                face_vertex_textures.push_back(&vertex_textures[std::stoi(face_vertex_str[1])  - 1]);
            }
            if (!face_vertex_str[2].empty())
            {
                face_vertex_normals.push_back(&vertex_normals[std::stoi(face_vertex_str[2])  - 1]);
            }
        }
        else
        {
            throw IllFormedFileException();
        }        
    }

    if (face_vertex_textures.size() != 0 && face_vertex_textures.size() != face_vertices.size())
    {
        throw IllFormedFileException();
    }
    if (face_vertex_normals.size() != 0 && face_vertex_normals.size() != face_vertices.size())
    {
        throw IllFormedFileException();
    }

    for (std::size_t i = 0; i < face_vertices.size() - 2; ++i)
    {
        Triangle triangle;

        triangle.m_a.m_pos = *face_vertices[0];
        triangle.m_b.m_pos = *face_vertices[i+1];
        triangle.m_c.m_pos = *face_vertices[i+2];

        if (face_vertex_textures.size() != 0)
        {
            triangle.m_a.m_texture = *face_vertex_textures[0];
            triangle.m_b.m_texture = *face_vertex_textures[i+1];
            triangle.m_c.m_texture = *face_vertex_textures[i+2];
        }

        if (face_vertex_normals.size() != 0)
        {
            triangle.m_a.m_normal = *face_vertex_normals[0];
            triangle.m_b.m_normal = *face_vertex_normals[i+1];
            triangle.m_c.m_normal = *face_vertex_normals[i+2];
        }

        mesh.m_triangles.push_back(std::move(triangle));
    }
}