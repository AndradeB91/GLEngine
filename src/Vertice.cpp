#include "Vertice.h"

Vertice::Vertice()
{
    this->coords.x = 0.0f;
    this->coords.y = 0.0f;
    this->coords.z = 0.0f;
}

Vertice::Vertice(GLfloat x, GLfloat y, GLfloat z)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.z = z;
}

Vertice::~Vertice()
{
}