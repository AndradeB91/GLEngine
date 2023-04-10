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

std::vector<std::pair<GLint, GLint> > Geometry::getBoundary()
{
    return this->_boundary;
}

GLfloat Geometry::getFaceQuality(GLint index)
{
    Face f = this->faces[index];

    Vertice A = this->vertices[f.ind0];
    Vertice B = this->vertices[f.ind1];
    Vertice C = this->vertices[f.ind2];

    glm::vec3 cA = A.coords;
    glm::vec3 cB = B.coords;
    glm::vec3 cC = C.coords;

    GLfloat a = glm::distance(cB, cC);
    GLfloat b = glm::distance(cA, cC);
    GLfloat c = glm::distance(cA, cB);

    GLfloat s = (a + b + c) / 2.0f;
    GLfloat inscribedCircleRadius = sqrt(((s - a) * (s - b) * (s - c)) / s);
    GLfloat circumscribedCircleRadius = (a * b * c) / (4.0f * sqrt(s * (s - a) * (s - b) * (s - c)));

    return 2.0f * (inscribedCircleRadius / circumscribedCircleRadius);
}

GLint Geometry::isEdgeIncluded(std::pair<GLint, GLint> edge)
{
    for (size_t i = 0; i < this->_boundary.size(); i++)
    {
        bool normalPair = this->_boundary[i].first == edge.first &&
                          this->_boundary[i].second == edge.second;

        bool invertedPair = this->_boundary[i].first == edge.second &&
                            this->_boundary[i].second == edge.first;

        if (normalPair || invertedPair)
        {
            return i;
        }
    }

    return -1;
}

void Geometry::checkEdgeInBoundary(std::pair<GLint, GLint> edge)
{
    GLint indexToErase = this->isEdgeIncluded(edge);

    if (indexToErase != -1)
    {
        this->_boundary.erase(this->_boundary.begin() + indexToErase);
    }
    else
    {
        this->_boundary.push_back(edge);
    }
}

void Geometry::updateBoundary(GLint ind0, GLint ind1, GLint ind2)
{
    std::pair<GLint, GLint> e0{ind0, ind1}, e1{ind1, ind2}, e2{ind2, ind0};

    this->checkEdgeInBoundary(e0);
    this->checkEdgeInBoundary(e1);
    this->checkEdgeInBoundary(e2);
}

void Geometry::setBoundary(std::vector<std::pair<GLint, GLint> > boundary)
{
    this->_boundary = boundary;
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
    for (size_t i = 0; i < this->vertices.size(); i++)
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
