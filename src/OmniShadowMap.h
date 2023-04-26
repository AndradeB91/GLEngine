#pragma once

#include <stdio.h>

#include "ShadowMap.h"

class OmniShadowMap : public ShadowMap
{
public:
    OmniShadowMap();

    bool init(unsigned int width, unsigned int height);

    void write();

    void read(GLenum TextureUnit);

    ~OmniShadowMap();

protected:
    GLuint _FBO, _shadowMap;
    GLuint _shadowWidth, _shadowHeight;
};