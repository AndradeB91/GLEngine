#include "PointLight.h"

PointLight::PointLight() : Light()
{
    this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_constant = 1.0f;
    this->_linear = 0.0f;
    this->_exponent = 0.0f;
}

PointLight::PointLight(GLfloat red,
                       GLfloat green,
                       GLfloat blue,
                       GLfloat ambientIntensity,
                       GLfloat diffuseIntensity,
                       GLfloat xPos,
                       GLfloat yPos,
                       GLfloat zPos,
                       GLfloat constant,
                       GLfloat linear,
                       GLfloat exponent) : Light(red,
                                                 green,
                                                 blue,
                                                 ambientIntensity,
                                                 diffuseIntensity)
{
    this->_position = glm::vec3(xPos, yPos, zPos);
    this->_constant = constant;
    this->_linear = linear;
    this->_exponent = exponent;
}

glm::vec3 PointLight::getPosition()
{
    return this->_position;
}

GLfloat PointLight::getConstant()
{
    return this->_constant;
}

GLfloat PointLight::getLinear()
{
    return this->_linear;
}

GLfloat PointLight::getExponent()
{
    return this->_exponent;
}

PointLight::~PointLight()
{
}
