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
                     GLfloat zDir,
                     GLfloat shadowWidth,
                     GLfloat shadowHeight);

    glm::vec3 getDirection();

    glm::mat4 calculateLightTransform();

    void setDirection(glm::vec3 direction);

    ~DirectionalLight();

private:
    glm::vec3 _direction;
};
