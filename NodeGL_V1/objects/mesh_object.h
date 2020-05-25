#pragma once
#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

struct Vertex {
    // position
    glm::vec3 Position;
    // texCoords
    glm::vec2 TexCoords;
    // normal
    glm::vec3 Normal;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;

    Vertex(glm::vec3 pos, glm::vec2 tex_coord, glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent)
    {
        Position = pos;
        TexCoords = tex_coord;
        Normal = normal;
        Tangent = tangent;
        Bitangent = bitangent;
    }
};

class MeshObject
{
public:
    MeshObject(std::string object_name, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~MeshObject();
    void DeleteMesh();
    void DeleteVectors();

    unsigned int GetVAO();
    unsigned int GetIndicesSize();

    void SetupMesh();

    std::string object_name;

private:
    // mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
};


void CalculateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int> indices);
void CalculateTangents(std::vector<Vertex>& vertices, std::vector<unsigned int> indices);

#endif
// MeshObject