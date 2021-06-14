#include "Shader.h"

Shader::Shader()
{
  this->_shaderID = 0;
}

void Shader::createFromString(const char *vertexCode, const char *fragmentCode)
{
  this->compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char *vertexLocation, const char *fragmentLocation)
{
  std::string vertexString = this->readFile(vertexLocation);
  std::string fragmentString = this->readFile(fragmentLocation);

  const char *vertexCode = vertexString.c_str();
  const char *fragmentCode = fragmentString.c_str();

  this->compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char *fileLocation)
{
  std::string content;
  std::ifstream fileStream(fileLocation, std::ios::in);

  if (!fileStream.is_open())
  {
    printf("Failed to read %s! File does not exist.", fileLocation);
    return "";
  }

  std::string line = "";
  while (!fileStream.eof())
  {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  return content;
}

void Shader::compileShader(const char *vertexCode, const char *fragmentCode)
{
  this->_shaderID = glCreateProgram();

  if (!this->_shaderID)
  {
    printf("Error creating shader program!\n");
    return;
  }

  this->addShader(this->_shaderID, vertexCode, GL_VERTEX_SHADER);
  this->addShader(this->_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar eLog[1024] = {0};

  glLinkProgram(this->_shaderID);
  glGetProgramiv(this->_shaderID, GL_LINK_STATUS, &result);

  if (!result)
  {
    glGetProgramInfoLog(this->_shaderID, sizeof(eLog), NULL, eLog);
    printf("Error linking program: '%s'\n", eLog);
    return;
  }

  // Skip validation temporarily because of a bug
  // glValidateProgram(this->_shaderID);
  // glGetProgramiv(this->_shaderID, GL_VALIDATE_STATUS, &result);
  //
  // if(!result) {
  //   glGetProgramInfoLog(this->_shaderID, sizeof(eLog), NULL, eLog);
  //   printf("Error validating program: '%s'\n", eLog);
  //   return;
  // }
}

GLuint Shader::getUniformLocation(const char *uniform)
{
  return glGetUniformLocation(this->_shaderID, uniform);
}

void Shader::useShader()
{
  glUseProgram(this->_shaderID);
}

void Shader::clearShader()
{
  if (this->_shaderID != 0)
  {
    glDeleteProgram(this->_shaderID);
    this->_shaderID = 0;
  }
}

void Shader::addShader(GLuint program, const char *shaderCode, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);

  const GLchar *code[1];
  code[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = strlen(shaderCode);

  glShaderSource(shader, 1, code, codeLength);
  glCompileShader(shader);

  GLint result = 0;
  GLchar eLog[1024] = {0};

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

  if (!result)
  {
    glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
    printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
    return;
  }

  glAttachShader(program, shader);
}

Shader::~Shader()
{
  this->clearShader();
}