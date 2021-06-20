#include "Window.h"

Window::Window(GLint width, GLint height)
{
    this->_width = width;
    this->_height = height;
    this->_bufferWidth = 0.0f;
    this->_bufferHeight = 0.0f;
    this->_lastX = 0.0f;
    this->_lastY = 0.0f;
    this->_xDelta = 0.0f;
    this->_yDelta = 0.0f;
    this->_mouseFirstMoved = true;
    this->initKeys();
}

void Window::initKeys()
{
    for (size_t i = 0; i < TOTAL_KEYS; i++)
    {
        this->_keys[i] = false;
    }
}

int Window::initialize()
{
    // Initialize GLFW
    if (!glfwInit())
    {
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

    if (!this->_mainWindow)
    {
        printf("GLFW window creation failed!\n");
        glfwTerminate();
        return 1;
    }

    // Get buffer size information
    glfwGetFramebufferSize(this->_mainWindow, &this->_bufferWidth, &this->_bufferHeight);

    // Set the context for GLEW to use
    glfwMakeContextCurrent(this->_mainWindow);

    // Handle Keys + Mouse Input
    glfwSetKeyCallback(this->_mainWindow, this->handleKeys);
    glfwSetCursorPosCallback(this->_mainWindow, this->handleMouse);
    glfwSetInputMode(this->_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(this->_mainWindow, this);

    return 0;
}

void Window::handleKeys(GLFWwindow *window, int key, int code, int action, int mode)
{
    Window *windowPointer = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < TOTAL_KEYS)
    {
        if (action == GLFW_PRESS)
        {
            windowPointer->_keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            windowPointer->_keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow *window, double xPos, double yPos)
{
    Window *windowPointer = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (windowPointer->_mouseFirstMoved)
    {
        windowPointer->_lastX = xPos;
        windowPointer->_lastY = yPos;
        windowPointer->_mouseFirstMoved = false;
    }

    windowPointer->_xDelta = xPos - windowPointer->_lastX;
    windowPointer->_yDelta = windowPointer->_lastY - yPos;

    windowPointer->_lastX = xPos;
    windowPointer->_lastY = yPos;
}

GLfloat Window::getBufferWidth()
{
    return this->_bufferWidth;
}

GLfloat Window::getBufferHeight()
{
    return this->_bufferHeight;
}

bool Window::getShouldClose()
{
    return glfwWindowShouldClose(this->_mainWindow);
}

bool *Window::getKeys()
{
    return this->_keys;
}

GLfloat Window::getXDelta()
{
    GLfloat delta = this->_xDelta;
    this->_xDelta = 0.0f;
    return delta;
}

GLfloat Window::getYDelta()
{
    GLfloat delta = this->_yDelta;
    this->_yDelta = 0.0f;
    return delta;
}

void Window::swapBuffers()
{
    glfwSwapBuffers(this->_mainWindow);
}

Window::~Window()
{
    glfwDestroyWindow(this->_mainWindow);
    glfwTerminate();
}
