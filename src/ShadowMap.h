#pragma once

#include <stdio.h>

#include <GL/glew.h>

class ShadowMap
{
public:
    ShadowMap();

    virtual bool init(unsigned int width, unsigned int height);

    virtual void write();

    virtual void read(GLenum TextureUnit);

    GLuint getShadowWidth() { return this->_shadowWidth; }
    GLuint getShadowHeight() { return this->_shadowHeight; }

    ~ShadowMap();

protected:
    GLuint _FBO, _shadowMap;
    GLuint _shadowWidth, _shadowHeight;
};