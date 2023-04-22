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
                                   GLfloat zDir,
                                   GLfloat shadowWidth,
                                   GLfloat shadowHeight) : Light(red,
                                                                 green,
                                                                 blue,
                                                                 ambientIntensity,
                                                                 diffuseIntensity,
                                                                 shadowWidth,
                                                                 shadowHeight)
{
    this->_direction = glm::vec3(xDir, yDir, zDir);
    this->_lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
}

glm::vec3 DirectionalLight::getDirection()
{
    return this->_direction;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
    this->_direction = direction;
}

glm::mat4 DirectionalLight::calculateLightTransform()
{
    return this->_lightProj * glm::lookAt(-this->_direction,
                                          glm::vec3(0.0f, 0.0f, 0.0f),
                                          glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight()
{
}