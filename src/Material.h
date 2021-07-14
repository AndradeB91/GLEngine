#pragma once

#include "GL/glew.h"

#include "math.h"

class Material
{

public:
    Material();

    Material(GLfloat specularIntensity, GLint shininessFactor);

    GLfloat getSpecularIntensity();
    GLint getShininess();
    GLint getShininessFactor();

    ~Material();

private:
    GLfloat _specularIntensity;
    GLint _shininess;
};