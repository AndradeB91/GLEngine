#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight();

    DirectionalLight(GLfloat red,
                     GLfloat green,
                     GLfloat blue,
                     GLfloat ambientIntensity,
                     GLfloat diffuseIntensity,
                     GLfloat xDir,
                     GLfloat yDir,
                     GLfloat zDir);

    glm::vec3 getDirection();

    void setDirection(glm::vec3 direction);

    ~DirectionalLight();

private:
    glm::vec3 _direction;
};
