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

    int id;

    Vertice operator%(const Vertice v)
    {
        Vertice vertice;
        float uvi = this->coords.y * v.coords.z - v.coords.y * this->coords.z;
        float uvj = v.coords.x * this->coords.z - this->coords.x * v.coords.z;
        float uvk = this->coords.x * v.coords.y - v.coords.x * this->coords.y;
        vertice.coords.x = uvi;
        vertice.coords.y = uvj;
        vertice.coords.z = uvk;
        return vertice;
    }

private:
};
