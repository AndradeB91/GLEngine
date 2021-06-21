#include "SpotLight.h"

SpotLight::SpotLight()
{
    this->_direction = glm::vec3(0.0f, -1.0f, 0.0f);
    this->_edge = 0.0f;
    this->_procEdge = cosf(glm::radians(this->_edge));
}

SpotLight::SpotLight(GLfloat red,
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
                     GLfloat edge) : PointLight(red,
                                                green,
                                                blue,
                                                ambientIntensity,
                                                diffuseIntensity,
                                                xPos,
                                                yPos,
                                                zPos,
                                                constant,
                                                linear,
                                                exponent)
{
    this->_direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    this->_edge = edge;
    this->_procEdge = cosf(glm::radians(this->_edge));
}

glm::vec3 SpotLight::getDirection()
{
    return this->_direction;
}

GLfloat SpotLight::getProcEdge()
{
    return this->_procEdge;
}

SpotLight::~SpotLight()
{
}
