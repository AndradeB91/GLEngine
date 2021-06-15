#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const unsigned int TOTAL_KEYS = 1024;

class Window
{
public:
  Window(GLint windowWidth = 800, GLint windowHeight = 600);

  int initialize();

  GLfloat getBufferWidth();
  GLfloat getBufferHeight();

  bool getShouldClose();

  bool *getKeys();

  GLfloat getXDelta();
  GLfloat getYDelta();

  void swapBuffers();

  ~Window();

private:
  GLFWwindow *_mainWindow;

  GLint _width, _height;
  GLint _bufferWidth, _bufferHeight;

  GLfloat _lastX, _lastY, _xDelta, _yDelta;
  bool _mouseFirstMoved;

  bool _keys[TOTAL_KEYS];

  void initKeys();

  static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
  static void handleMouse(GLFWwindow *window, double xPos, double yPos);
};