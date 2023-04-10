#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <utility>

#include "Vertice.h"
#include "Face.h"

class Geometry
{
public:
    Geometry();

    ~Geometry();

    GLint getNumVertices();
    GLint getNumFaces();
    GLfloat getFaceQuality(GLint index);

    std::vector<std::pair<GLint, GLint> > getBoundary();

    std::vector<Face> getFaces();

    void updateBoundary(GLint ind0, GLint ind1, GLint ind2);
    void setBoundary(std::vector<std::pair<GLint, GLint> > boundary);

    void addVertice(GLfloat x, GLfloat y, GLfloat z);
    void addNormal(GLfloat x, GLfloat y, GLfloat z);
    void addFace(GLint ind0, GLint ind1, GLint ind2);

    void removeFace(GLint index);

    void updateGeometryByModelMatrix(glm::mat4 modelMatrix);

    std::vector<Vertice> vertices;
    std::vector<Vertice> normals;
    std::vector<Face> faces;

private:
    GLint _numVertices, _numFaces;

    std::vector<std::pair<GLint, GLint> > _boundary;

    GLint isEdgeIncluded(std::pair<GLint, GLint> edge);
    void checkEdgeInBoundary(std::pair<GLint, GLint> edge);
};