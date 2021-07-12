#include "Geometry.h"

Geometry::Geometry()
{
}

void Geometry::setNumVertices(int numVertices)
{
    this->_numVertices = numVertices;
}

void Geometry::setNumFaces(GLint numFaces)
{
    this->_numFaces = numFaces;
}

GLint Geometry::getNumVertices()
{
    return this->_numVertices;
}

GLint Geometry::getNumFaces()
{
    return this->_numFaces;
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

Geometry::~Geometry()
{
}
