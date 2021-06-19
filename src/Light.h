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
          GLfloat xDir,
          GLfloat yDir,
          GLfloat zDir,
          GLfloat diffuseIntensity);

    glm::vec3 getColour();
    glm::vec3 getDirection();

    GLfloat getAmbientIntensity();
    GLfloat getDiffuseIntensity();

    ~Light();

private:
    glm::vec3 _colour;
    glm::vec3 _direction;

    GLfloat _ambientIntensity;
    GLfloat _diffuseIntensity;
};
