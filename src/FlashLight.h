#pragma once

#include "SpotLight.h"
#include "Camera.h"

class FlashLight : public SpotLight
{

public:
    FlashLight();

    FlashLight(GLfloat red,
               GLfloat green,
               GLfloat blue,
               GLfloat ambientIntensity,
               GLfloat diffuseIntensity,
               GLfloat xPos,
               GLfloat yPos,
               GLfloat zPos,
               GLfloat xDir,
               GLfloat yDir,
               GLfloat zDir,
               GLfloat constant,
               GLfloat linear,
               GLfloat exponent,
               GLfloat edge);

    void update(glm::vec3 position, glm::vec3 direction);

    ~FlashLight();
};
