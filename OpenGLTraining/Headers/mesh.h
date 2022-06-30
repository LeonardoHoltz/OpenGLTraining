// mesh.h

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "shader.h"
#include "texture.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

class Mesh {

    enum AttributePointers { vPosition = 0, vNormals = 1, vTextureCoord = 2};

public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif // MESH_H
