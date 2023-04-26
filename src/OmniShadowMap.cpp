#include "OmniShadowMap.h"

OmniShadowMap::OmniShadowMap() : ShadowMap()
{
}

bool OmniShadowMap::init(unsigned int width, unsigned int height)
{
    this->_shadowWidth = width;
    this->_shadowHeight = height;

    // First we'll create a framebuffer object for rendering the depth map:
    glGenFramebuffers(1, &this->_FBO);

    // Next we create a 2D texture that we'll use as the framebuffer's depth buffer:
    glGenTextures(1, &this->_shadowMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->_shadowMap);

    for (size_t i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, this->_FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->_shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer error: %s\n", Status);
        return false;
    }

    return true;
}

void OmniShadowMap::write()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->_FBO);
}

void OmniShadowMap::read(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->_shadowMap);
}

OmniShadowMap::~OmniShadowMap()
{
    if (this->_FBO)
    {
        glDeleteFramebuffers(1, &this->_FBO);
    }

    if (this->_shadowMap)
    {
        glDeleteTextures(1, &this->_shadowMap);
    }
}
