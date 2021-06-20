#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
    Light();

    Light(GLfloat red,
          GLfloat green,
          GLfloat blue,
          GLfloat ambientIntensity,
          GLfloat diffuseIntensity);

    glm::vec3 getColour();

    GLfloat getAmbientIntensity();
    GLfloat getDiffuseIntensity();

    ~Light();

protected:
    glm::vec3 _colour;
    GLfloat _ambientIntensity;
    GLfloat _diffuseIntensity;
};
