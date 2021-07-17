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

void Geometry::updateGeometryByModelMatrix(glm::mat4 modelMatrix)
{
    for (size_t i = 0; i < this->getNumVertices(); i++)
    {
        Vertice vertice = this->vertices[i];
        glm::vec4 modVert = modelMatrix * glm::vec4(vertice.coords.x,
                                                    vertice.coords.y,
                                                    vertice.coords.z,
                                                    1.0f);

        this->vertices[i] = Vertice(modVert.x, modVert.y, modVert.z);
    }
}

Geometry::~Geometry()
{
}
