#include "Vertice.h"

static int sNextId = 0;

Vertice::Vertice()
{
    this->coords.x = 0.0f;
    this->coords.y = 0.0f;
    this->coords.z = 0.0f;
    this->id = ++sNextId;
}

Vertice::Vertice(GLfloat x, GLfloat y, GLfloat z)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.z = z;
    this->id = ++sNextId;
}

Vertice::~Vertice()
{
}