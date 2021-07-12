#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <list>

#include "Face.h"

class Vertice
{

public:
    Vertice();

    Vertice(GLfloat x, GLfloat y, GLfloat z);

    ~Vertice();

    glm::vec3 coords;

private:
};
