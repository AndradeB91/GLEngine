#include "Texture.h"

Texture::Texture()
{
    this->_textureID = 0;
    this->_width = 0;
    this->_height = 0;
    this->_bitDepth = 0;
    this->_fileLocation = "";
}

Texture::Texture(const char *fileLocation)
{
    this->_textureID = 0;
    this->_width = 0;
    this->_height = 0;
    this->_bitDepth = 0;
    this->_fileLocation = fileLocation;
}

bool Texture::loadTexture()
{
    unsigned char *texData = stbi_load(this->_fileLocation,
                                       &this->_width,
                                       &this->_height,
                                       &this->_bitDepth,
                                       0);

    if (!texData)
    {
        printf("Failed to find %s\n", this->_fileLocation);
        return false;
    }

    glGenTextures(1, &this->_textureID);
    glBindTexture(GL_TEXTURE_2D, this->_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 this->_width,
                 this->_height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 texData);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);

    return true;
}

bool Texture::loadTextureWithAlpha()
{
    unsigned char *texData = stbi_load(this->_fileLocation,
                                       &this->_width,
                                       &this->_height,
                                       &this->_bitDepth,
                                       0);

    if (!texData)
    {
        printf("Failed to find %s\n", this->_fileLocation);
        return false;
    }

    glGenTextures(1, &this->_textureID);
    glBindTexture(GL_TEXTURE_2D, this->_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 this->_width,
                 this->_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 texData);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);

    return true;
}

void Texture::useTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_textureID);
}

void Texture::clearTexture()
{
    glDeleteTextures(1, &this->_textureID);
    this->_textureID = 0;
    this->_width = 0;
    this->_height = 0;
    this->_bitDepth = 0;
    this->_fileLocation = "";
}

Texture::~Texture()
{
    clearTexture();
}
