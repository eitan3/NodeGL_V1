#include "mesh_object.h"

MeshObject::MeshObject(std::string object_name, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	this->object_name = object_name;
	this->vertices = vertices;
	this->indices = indices;
    SetupMesh();
}

MeshObject::~MeshObject()
{
    DeleteMesh();
    DeleteVectors();
}

void MeshObject::DeleteMesh()
{
    if (VBO)
        glDeleteBuffers(1, &VBO);
    if (EBO)
        glDeleteBuffers(1, &EBO);
    if (VAO)
        glDeleteVertexArrays(1, &VAO);
    VBO = 0;
    EBO = 0;
    VAO = 0;
}

void MeshObject::DeleteVectors()
{
    this->vertices.clear();
    this->indices.clear();
}

unsigned int MeshObject::GetVAO()
{
	return VAO;
}

void MeshObject::SetupMesh()
{
    if (VBO || EBO || VAO)
        DeleteMesh();

    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}







void CalculateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int> indices)
{
    std::vector<glm::vec3>mNormals = std::vector<glm::vec3>(vertices.size(), glm::vec3(0, 0, 0));

    // For each triangular face
    for (unsigned int i = 0; i < indices.size() / 3; i += 3) {

        // Get the three vertices index of the current face
        unsigned int v1 = indices.at(i * 3);
        unsigned int v2 = indices.at(i * 3 + 1);
        unsigned int v3 = indices.at(i * 3 + 2);

        assert(v1 < vertices.size());
        assert(v2 < vertices.size());
        assert(v3 < vertices.size());

        // Compute the normal of the face
        glm::vec3 p = vertices.at(v1).Position;
        glm::vec3 q = vertices.at(v2).Position;
        glm::vec3 r = vertices.at(v3).Position;
        glm::vec3 normal = glm::cross(q - p, r - p);// (q - p).cross(r - p);
        normal = glm::normalize(normal);

        // Add the face surface normal to the sum of normals at
        // each vertex of the face
        mNormals[v1] += normal;
        mNormals[v2] += normal;
        mNormals[v3] += normal;
    }

    // Normalize the normal at each vertex
    for (unsigned int i = 0; i < vertices.size(); i++) {
        assert(mNormals[i].length() > 0);
        vertices.at(i).Normal = glm::normalize(mNormals[i]);
    }
}

glm::vec3 CalculateTangentHardness(glm::vec3 tangent, glm::vec3 bitangent, glm::vec3 normal)
{
    // Gram-Schmidt orthogonalize
    tangent = glm::normalize(tangent - normal * glm::dot(normal, tangent));

    // Calculate handedness
    if (glm::dot(glm::cross(normal, tangent), bitangent) < 0.0f) {
        tangent = tangent * -1.0f;
    }
    return tangent;
}

void CalculateTangents(std::vector<Vertex>& vertices, std::vector<unsigned int> indices) {

    std::vector<glm::vec3> mTangents = std::vector<glm::vec3>(vertices.size(), glm::vec3(0, 0, 0));
    std::vector<glm::vec3> mBitangents = std::vector<glm::vec3>(vertices.size(), glm::vec3(0, 0, 0));

    // For each face
    for (unsigned int i = 0; i < indices.size() / 3; i += 3)
    {
        // Get the three vertices index of the face
        unsigned int v1 = indices.at(i * 3);
        unsigned int v2 = indices.at(i * 3 + 1);
        unsigned int v3 = indices.at(i * 3 + 2);

        assert(v1 < getNbVertices());
        assert(v2 < getNbVertices());
        assert(v3 < getNbVertices());

        // Get the vertices positions
        glm::vec3 p = vertices.at(v1).Position;
        glm::vec3 q = vertices.at(v2).Position;
        glm::vec3 r = vertices.at(v3).Position;

        // Get the texture coordinates of each vertex
        glm::vec2 uvP = vertices.at(v1).TexCoords;
        glm::vec2 uvQ = vertices.at(v2).TexCoords;
        glm::vec2 uvR = vertices.at(v3).TexCoords;

        // Get the three edges
        glm::vec3 edge1 = q - p;
        glm::vec3 edge2 = r - p;
        glm::vec2 edge1UV = uvQ - uvP;
        glm::vec2 edge2UV = uvR - uvP;

        float cp = edge1UV.y * edge2UV.x - edge1UV.x * edge2UV.y;

        // Compute the tangent
        if (cp != 0.0f) {
            //float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            //glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            //glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            float factor = 1.0f / cp;

            glm::vec3 bitangent = (edge2 * -edge1UV.x + edge1 * edge2UV.x) * factor;
            vertices.at(v1).Bitangent += bitangent;
            vertices.at(v2).Bitangent += bitangent;
            vertices.at(v3).Bitangent += bitangent;

            glm::vec3 tangent = (edge1 * -edge2UV.y + edge2 * edge1UV.y) * factor;
            vertices.at(v1).Tangent += CalculateTangentHardness(tangent, bitangent, vertices.at(v1).Normal);
            vertices.at(v2).Tangent += CalculateTangentHardness(tangent, bitangent, vertices.at(v2).Normal);
            vertices.at(v3).Tangent += CalculateTangentHardness(tangent, bitangent, vertices.at(v3).Normal);
        }
    }
}