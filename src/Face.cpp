#include "Face.h"

Face::Face()
{
}

Face::Face(GLint ind0, GLint ind1, GLint ind2)
{
    this->ind0 = ind0;
    this->ind1 = ind1;
    this->ind2 = ind2;
}

Face::~Face()
{
}

int Face::getIndex(int i)
{
    if (i == 0)
        return this->ind0;
    else if (i == 1)
        return this->ind1;
    else
        return this->ind2;
}