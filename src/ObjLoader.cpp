#include "../include/ObjLoader.hpp"

#include "../include/Resources/Geometry.hpp"
#include "../include/Rendering/Vertex.hpp"

#include <fstream>
#include <iostream>

namespace Utility {
glm::vec3 ObjLoader::parseVec3(const std::string& str) {
    float x, y, z;
    std::sscanf(str.data(), "%f %f %f", &x, &y, &z);

    return glm::vec3(x, y, z);
}

glm::vec2 ObjLoader::parseVec2(const std::string& str) {
    float x, y;
    std::sscanf(str.data(), "%f %f", &x, &y);

    return glm::vec2(x, y);
}

std::array<std::tuple<int, int, int>, 3> ObjLoader::parseFace(const std::string& str) {
    int p1, p2, p3, t1, t2, t3, n1, n2, n3;
    std::sscanf(str.data(), "%i/%i/%i %i/%i/%i %i/%i/%i",
                &p1, &t1, &n1,
                &p2, &t2, &n2,
                &p3, &t3, &n3);

    return std::array<std::tuple<int, int, int>, 3>{
        std::tuple<int, int, int>(p1 - 1, t1 - 1, n1 - 1),
        std::tuple<int, int, int>(p2 - 1, t2 - 1, n2 - 1),
        std::tuple<int, int, int>(p3 - 1, t3 - 1, n3 - 1)};
}

const Geometry* ObjLoader::loadObj(const std::string& filename) {
    // load geometry data
    std::ifstream fs(filename);
    std::string line;

    std::vector<glm::vec3> positions, normals;
    std::vector<glm::vec2> textureCoods;
    std::vector<std::array<std::tuple<int, int, int>, 3>> faces;

    if (fs.good()) {
        while (fs.good()) {
            std::getline(fs, line);

            if (line.starts_with("mtllib ")) {
            }
            else if (line.starts_with("v ")) {
                positions.emplace_back(parseVec3(line.substr(2)));
            }
            else if (line.starts_with("vt ")) {
                textureCoods.emplace_back(parseVec2(line.substr(3)));
            }
            else if (line.starts_with("vn ")) {
                normals.emplace_back(parseVec3(line.substr(3)));
            }
            else if (line.starts_with("f ")) {
                faces.emplace_back(parseFace(line.substr(2)));
            }
        }
    }

    std::vector<std::tuple<int, int, int>> vertexIndices;
    std::vector<unsigned int> indices;

    for (const auto& face : faces) {
        for (auto& faceIndices : face) {
            int index = 0;

            while (index < vertexIndices.size()) {
                if (vertexIndices[index] == faceIndices) {
                    break;
                }

                index++;
            }

            if (!(index < vertexIndices.size())) {
                vertexIndices.emplace_back(faceIndices);
            }

            indices.emplace_back(index);
        }
    }

    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {        
        auto& [p, t, n] = vertexIndices[i];        
        vertices.emplace_back(Vertex{positions[p], normals[n], textureCoods[t]});
    }

    Geometry* geometry = new Geometry();
    geometry->updateBuffers(vertices, indices);

    return geometry;
}
} // namespace Utility