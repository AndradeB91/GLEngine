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
                      unsigned int numOfIndices,
                      unsigned int layouts,
                      GLint layoutsSizes[],
                      GLenum layoutsTypes[],
                      unsigned int lineSize,
                      unsigned int shifts[])
{
    this->_indexCount = numOfIndices;

    this->bindBuffers(vertices, indices, numOfVertices, numOfIndices);

    for (unsigned int i = 0; i < layouts; i++)
    {
        this->setLayoutLocation(i,
                                layoutsSizes[i],
                                layoutsTypes[i],
                                GL_FALSE,
                                sizeof(vertices[0]) * lineSize,
                                (void *)(sizeof(vertices[0]) * shifts[i]));
    }

    this->unbindBuffers();
}

void Mesh::setLayoutLocation(GLuint location,
                             GLint size,
                             GLenum type,
                             GLboolean normalized,
                             GLsizei stride,
                             const void *pointer)
{
    glVertexAttribPointer(location, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(location);
}

void Mesh::bindBuffers(GLfloat *vertices,
                       unsigned int *indices,
                       unsigned int numOfVertices,
                       unsigned int numOfIndices)
{
    glGenVertexArrays(1, &this->_VAO);
    glBindVertexArray(this->_VAO);

    glGenBuffers(1, &this->_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);
}

void Mesh::unbindBuffers()
{
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