#pragma once

#include <GL/glew.h>
#include <vector>

class Primitive
{
public:
    static void generateCube(
        float size,
        GLfloat *&vertices,
        unsigned int *&indices,
        int &numVertices,
        int &numIndices);

    static void generateSphere(
        int rings,
        int sectors,
        float radius,
        GLfloat *&vertices,
        unsigned int *&indices,
        int &numVertices,
        int &numIndices);
};
