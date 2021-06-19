#include "Light.h"

Light::Light()
{
    this->_colour = glm::vec3(1.0f, 1.0f, 1.0f);
    this->_ambientIntensity = 1.0f;
    this->_direction = glm::vec3(0.0f, -1.0f, 0.0f);
    this->_diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red,
             GLfloat green,
             GLfloat blue,
             GLfloat ambientIntensity,
             GLfloat xDir,
             GLfloat yDir,
             GLfloat zDir,
             GLfloat diffuseIntensity)
{
    this->_colour = glm::vec3(red, green, blue);
    this->_ambientIntensity = ambientIntensity;
    this->_direction = glm::vec3(xDir, yDir, zDir);
    this->_diffuseIntensity = diffuseIntensity;
}

glm::vec3 Light::getColour()
{
    return this->_colour;
}

glm::vec3 Light::getDirection()
{
    return this->_direction;
}

GLfloat Light::getAmbientIntensity()
{
    return this->_ambientIntensity;
}

GLfloat Light::getDiffuseIntensity()
{
    return this->_diffuseIntensity;
}

Light::~Light()
{
}
