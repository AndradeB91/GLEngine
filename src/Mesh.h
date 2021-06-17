#pragma once

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();

    void createMesh(GLfloat *vertices,
                    unsigned int *indices,
                    unsigned int numOfVertices,
                    unsigned int numOfIndices,
                    unsigned int layouts,
                    GLint sizes[],
                    GLenum layoutsTypes[],
                    unsigned int lineSize,
                    unsigned int shifts[]);

    void renderMesh();

    void clearMesh();

    ~Mesh();

private:
    GLuint _VAO, _VBO, _IBO;
    GLsizei _indexCount;

    void bindBuffers(GLfloat *vertices,
                     unsigned int *indices,
                     unsigned int numOfVertices,
                     unsigned int numOfIndices);

    void unbindBuffers();

    void setLayoutLocation(GLuint location,
                           GLint size,
                           GLenum type,
                           GLboolean normalized,
                           GLsizei stride,
                           const void *pointer);
};