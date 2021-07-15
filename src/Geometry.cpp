#include "Geometry.h"

Geometry::Geometry()
{
}

GLint Geometry::getNumVertices()
{
    return this->vertices.size();
}

GLint Geometry::getNumFaces()
{
    return this->faces.size();
}

void Geometry::addVertice(GLfloat x, GLfloat y, GLfloat z)
{
    this->vertices.push_back(Vertice(x, y, z));
}

void Geometry::addNormal(GLfloat x, GLfloat y, GLfloat z)
{
    this->normals.push_back(Vertice(x, y, z));
}

void Geometry::addFace(GLint ind0, GLint ind1, GLint ind2)
{
    this->faces.push_back(Face(ind0, ind1, ind2));
}

void Geometry::removeFace(GLint index)
{
    this->faces.erase(this->faces.begin() + index);
}

Geometry::~Geometry()
{
}
