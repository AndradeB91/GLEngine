#include "Window.h"

Window::Window() {
  this->_width = 800;
  this->_height = 600;
};

Window::Window(GLint width, GLint height) {
  this->_width = width;
  this->_height = height;
};

int Window::initialize() {
  // Initialize GLFW
  if (!glfwInit()) {
    printf("GLFW initialization failed!\n");
    glfwTerminate();
    return 1;
  }

  // Setup GLFW window properties

  // OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Core profile = No backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  this->_mainWindow = glfwCreateWindow(this->_width, this->_height, "Main window", NULL, NULL);

  if (!this->_mainWindow) {
    printf("GLFW window creation failed!\n");
    glfwTerminate();
    return 1;
  }

  // Get buffer size information
  glfwGetFramebufferSize(this->_mainWindow, &this->_bufferWidth, &this->_bufferHeight);

  // Set the context for GLEW to use
  glfwMakeContextCurrent(this->_mainWindow);

  // Allow modern extension features
  glewExperimental = GL_TRUE;

  GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(this->_mainWindow);
		glfwTerminate();
		return 1;
	}

  glEnable(GL_DEPTH_TEST);

  // Setup viewport size
  glViewport(0, 0, this->_bufferWidth, this->_bufferHeight);

  return 0;
}

GLfloat Window::getBufferWidth() { 
  return this->_bufferWidth; 
};

GLfloat Window::getBufferHeight() { 
  return this->_bufferHeight; 
};

bool Window::getShouldClose() { 
  return glfwWindowShouldClose(this->_mainWindow); 
};

void Window::swapBuffers() { 
  glfwSwapBuffers(this->_mainWindow); 
}

Window::~Window() {
  glfwDestroyWindow(this->_mainWindow);
  glfwTerminate();
};

