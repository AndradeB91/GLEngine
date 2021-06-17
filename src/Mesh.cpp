#include "Mesh.h"

Mesh::Mesh()
{
    this->_VAO = 0;
    this->_VBO = 0;
    this->_IBO = 0;
    this->_indexCount = 0;
}

void Mesh::createMesh(GLfloat *vertices,
                      unsigned int *indices,
                      unsigned int numOfVertices,
                      unsigned int numOfIndices)
{
    this->_indexCount = numOfIndices;

    glGenVertexArrays(1, &this->_VAO);
    glBindVertexArray(this->_VAO);

    glGenBuffers(1, &this->_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    // Pointing to the layout (location = 0) in vertex shader to store a vertice position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
    glEnableVertexAttribArray(0);

    // Pointing to the layout (location = 1) in vertex shader to store uv texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void *)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);

    // unbind VBO, IBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::renderMesh()
{
    glBindVertexArray(this->_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_IBO);
    glDrawElements(GL_TRIANGLES, this->_indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::clearMesh()
{
    if (this->_IBO != 0)
    {
        glDeleteBuffers(1, &this->_IBO);
        this->_IBO = 0;
    }

    if (this->_VBO != 0)
    {
        glDeleteBuffers(1, &this->_VBO);
        this->_VBO = 0;
    }

    if (this->_VAO != 0)
    {
        glDeleteVertexArrays(1, &this->_VAO);
        this->_VAO = 0;
    }

    this->_indexCount = 0;
}

Mesh::~Mesh()
{
    this->clearMesh();
}