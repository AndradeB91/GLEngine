#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    this->_FBO = 0;
    this->_shadowMap = 0;
}

bool ShadowMap::init(unsigned int width, unsigned int height)
{
    this->_shadowWidth = width;
    this->_shadowHeight = height;

    // First we'll create a framebuffer object for rendering the depth map:
    glGenFramebuffers(1, &this->_FBO);

    // Next we create a 2D texture that we'll use as the framebuffer's depth buffer:
    glGenTextures(1, &this->_shadowMap);
    glBindTexture(GL_TEXTURE_2D, this->_shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // With the generated depth texture we can attach it as the framebuffer's depth buffer:
    glBindFramebuffer(GL_FRAMEBUFFER, this->_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer error: %s\n", Status);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void ShadowMap::write()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->_FBO);
}

void ShadowMap::read(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, this->_shadowMap);
}

ShadowMap::~ShadowMap()
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
