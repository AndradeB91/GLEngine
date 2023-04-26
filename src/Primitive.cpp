#include "Primitive.h"

const float PI = 3.14159265358979323846f;

void Primitive::generateCube(
    float size,
    GLfloat *&vertices,
    unsigned int *&indices,
    int &numVertices,
    int &numIndices)
{
    GLfloat _vertices[] = {
        -size, -size, size,
        -size, -size, -size,
        size, -size, -size,
        size, -size, size,
        -size, size, size,
        -size, size, -size,
        size, size, -size,
        size, size, size};

    unsigned int _indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7};

    numVertices = 24;
    numIndices = 36;

    vertices = new GLfloat[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        vertices[i] = _vertices[i];
    }

    indices = new GLuint[numIndices];
    for (int i = 0; i < numIndices; i++)
    {
        indices[i] = _indices[i];
    }
}

void Primitive::generateSphere(
    int rings,
    int sectors,
    float radius,
    GLfloat *&vertices,
    unsigned int *&indices,
    int &numVertices,
    int &numIndices)
{
    std::vector<GLfloat> vertexVec;
    std::vector<GLuint> indexVec;
    const float R = 1.0f / static_cast<float>(rings - 1);
    const float S = 1.0f / static_cast<float>(sectors - 1);

    for (int r = 0; r < rings; ++r)
    {
        for (int s = 0; s < sectors; ++s)
        {
            const float y = static_cast<float>(sin(-PI / 2 + PI * r * R));
            const float x = static_cast<float>(cos(2 * PI * s * S) * sin(PI * r * R));
            const float z = static_cast<float>(sin(2 * PI * s * S) * sin(PI * r * R));

            vertexVec.push_back(x * radius);
            vertexVec.push_back(y * radius);
            vertexVec.push_back(z * radius);
        }
    }

    for (int r = 0; r < rings - 1; ++r)
    {
        for (int s = 0; s < sectors - 1; ++s)
        {
            const int idx = r * sectors + s;
            indexVec.push_back(idx);
            indexVec.push_back(idx + sectors);
            indexVec.push_back(idx + sectors + 1);

            indexVec.push_back(idx);
            indexVec.push_back(idx + sectors + 1);
            indexVec.push_back(idx + 1);
        }
    }

    numVertices = vertexVec.size();
    vertices = new GLfloat[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        vertices[i] = vertexVec[i];
    }

    numIndices = indexVec.size();
    indices = new GLuint[numIndices];
    for (int i = 0; i < numIndices; i++)
    {
        indices[i] = indexVec[i];
    }
}
