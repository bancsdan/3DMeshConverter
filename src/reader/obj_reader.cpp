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
            if (Utility::startsWith(lineVect[0], vn))
            {
                readVector(lineVect, vertex_normals);
            }
            else if (Utility::startsWith(lineVect[0], vt))
            {
                readVector(lineVect, vertex_textures);
            }
            else if (Utility::startsWith(lineVect[0], v))
            {
                readVector(lineVect, vertices);
            }
            else if(Utility::startsWith(lineVect[0], f))
            {
                readFace(lineVect, result);
            }            
            else if (Utility::startsWith(lineVect[0], "mtllib"))
            {
                if (lineVect.size() > 1)
                {
                    result.m_material_file = lineVect[1];
                }
            }
        }

    }

    //for (const auto& ve: vertices)
    //    std::cout << "x: " << ve[0] << "y: " << ve[1] << "z: " << ve[2] << "w: " << ve[3] << '\n';

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

void ObjReader::readFace(const std::vector<std::string>& line, MeshData& mesh) const
{
    (void)line;
    (void)mesh;
}