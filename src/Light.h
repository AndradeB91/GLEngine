#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ShadowMap.h"

class Light
{
public:
    Light();

    Light(GLfloat red,
          GLfloat green,
          GLfloat blue,
          GLfloat ambientIntensity,
          GLfloat diffuseIntensity,
          GLfloat shadowWidth = 1024,
          GLfloat shadowHeight = 1024);

    glm::vec3 getColour();

    GLfloat getAmbientIntensity();
    GLfloat getDiffuseIntensity();

    ShadowMap *getShadowMap() { return this->_shadowMap; };

    ~Light();

protected:
    glm::vec3 _colour;
    GLfloat _ambientIntensity;
    GLfloat _diffuseIntensity;

    glm::mat4 _lightProj;

    ShadowMap *_shadowMap;
};
