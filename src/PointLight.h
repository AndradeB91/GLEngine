#pragma once

#include "Light.h"
#include "Model.h"
#include "Primitive.h"

class PointLight : public Light
{
public:
    PointLight();

    PointLight(GLfloat red,
               GLfloat green,
               GLfloat blue,
               GLfloat ambientIntensity,
               GLfloat diffuseIntensity,
               GLfloat xPos,
               GLfloat yPos,
               GLfloat zPos,
               GLfloat constant,
               GLfloat linear,
               GLfloat exponent);

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    GLfloat getConstant();
    GLfloat getLinear();
    GLfloat getExponent();

    Model *getModel();

    ~PointLight();

protected:
    glm::vec3 _position;

    GLfloat _constant, _linear, _exponent;

    Model *_model;
};
