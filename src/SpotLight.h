#pragma once

#include "PointLight.h"

class SpotLight : public PointLight
{

public:
    SpotLight();

    SpotLight(GLfloat red,
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

    glm::vec3 getDirection();

    GLfloat getProcEdge();

    ~SpotLight();

protected:
    glm::vec3 _direction;

    GLfloat _edge, _procEdge;
};
