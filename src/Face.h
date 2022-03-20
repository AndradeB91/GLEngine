#pragma once

#include <GL/glew.h>

class Face
{

public:
    Face();

    Face(GLint ind0, GLint ind1, GLint ind2);

    ~Face();

    GLint ind0, ind1, ind2;

    GLint getIndex(int i);

private:
};
