#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Window
{
public:
  Window();

  Window(GLint windowWidth, GLint windowHeight);

  int initialize();

  GLfloat getBufferWidth();
  GLfloat getBufferHeight();

  bool getShouldClose();

  void swapBuffers();

  ~Window();

private:
  GLFWwindow *_mainWindow;
  GLint _width, _height;
  GLint _bufferWidth, _bufferHeight;
};