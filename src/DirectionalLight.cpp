#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
    this->_direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red,
                                   GLfloat green,
                                   GLfloat blue,
                                   GLfloat ambientIntensity,
                                   GLfloat diffuseIntensity,
                                   GLfloat xDir,
                                   GLfloat yDir,
                                   GLfloat zDir) : Light(red,
                                                         green,
                                                         blue,
                                                         ambientIntensity,
                                                         diffuseIntensity)
{
    this->_direction = glm::vec3(xDir, yDir, zDir);
}

glm::vec3 DirectionalLight::getDirection()
{
    return this->_direction;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
    this->_direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}