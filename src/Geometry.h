#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertice.h"
#include "Face.h"

class Geometry
{
public:
    Geometry();

    ~Geometry();

    GLint getNumVertices();
    GLint getNumFaces();

    std::vector<Face> getFaces();

    void addVertice(GLfloat x, GLfloat y, GLfloat z);
    void addNormal(GLfloat x, GLfloat y, GLfloat z);
    void addFace(GLint ind0, GLint ind1, GLint ind2);

    void removeFace(GLint index);

    std::vector<Vertice> vertices;
    std::vector<Vertice> normals;
    std::vector<Face> faces;

private:
    GLint _numVertices, _numFaces;
};