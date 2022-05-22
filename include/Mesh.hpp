#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Textures
{
    unsigned int id;
    std::string path;
    std::string type;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Textures> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures);
    void Draw(Shader &shader);
private:
    unsigned int VBO, EBO;
    void setupMesh();
};

#endif