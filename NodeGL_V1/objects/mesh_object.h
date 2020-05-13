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
};

class MeshObject
{
public:
    MeshObject(std::string object_name, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~MeshObject();
    void DeleteMesh();
    void DeleteVectors();

    unsigned int GetVAO();

    void SetupMesh();

private:
    // mesh Data
    std::string object_name;
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
};


void CalculateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int> indices);
void CalculateTangents(std::vector<Vertex>& vertices, std::vector<unsigned int> indices);

#endif
// MeshObject