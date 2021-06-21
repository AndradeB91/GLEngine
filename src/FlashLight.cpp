#include "FlashLight.h"

FlashLight::FlashLight()
{
}

FlashLight::FlashLight(GLfloat red,
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
                       GLfloat edge) : SpotLight(red,
                                                 green,
                                                 blue,
                                                 ambientIntensity,
                                                 diffuseIntensity,
                                                 xPos,
                                                 yPos,
                                                 zPos,
                                                 xDir,
                                                 yDir,
                                                 zDir,
                                                 constant,
                                                 linear,
                                                 exponent,
                                                 edge)
{
}

void FlashLight::update(glm::vec3 position, glm::vec3 direction)
{
    this->_position = position;
    this->_direction = direction;
}

FlashLight::~FlashLight()
{
}
