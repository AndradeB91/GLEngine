#pragma once

#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
public:
    Texture();

    Texture(const char *fileLocation);

    void loadTexture();
    void useTexture();
    void clearTexture();

    ~Texture();

private:
    GLuint _textureID;
    int _width, _height, _bitDepth;

    const char *_fileLocation;
};
