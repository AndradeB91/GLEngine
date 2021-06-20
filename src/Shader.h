#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader();

    void createFromString(const char *vertexCode, const char *fragmentCode);
    void createFromFiles(const char *vertexLocation, const char *fragmentLocation);

    std::string readFile(const char *fileLocation);

    void setUniformMatrix4fv(const char *uniform, glm::mat4 matrix);
    void setUniform3f(const char *uniform, glm::vec3 vec);
    void setUniform1f(const char *uniform, GLfloat value);
    void setUniform1i(const char *uniform, GLuint value);

    void useShader();
    void clearShader();

    ~Shader();

private:
    GLuint _shaderID, _projection, _model;

    void compileShader(const char *vertexCode, const char *fragmentCode);

    void addShader(GLuint program, const char *shaderCode, GLenum shaderType);

    GLuint getUniformLocation(const char *uniform);
};