#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include <GLFW/glfw3.h>

#include "Window.h"
#include "MousePicker.h"

class Camera
{
public:
    Camera(
        GLfloat xPos = 0.0f,
        GLfloat yPos = 0.0f,
        GLfloat zPos = 0.0f,
        GLfloat xUp = 0.0f,
        GLfloat yUp = 1.0f,
        GLfloat zUp = 0.0f,
        GLfloat yaw = 0.0f,
        GLfloat pitch = 0.0f,
        GLfloat movementSpeed = 0.0f,
        GLfloat turnSpeed = 0.0f);

    void listenKeys(Window *window, bool *keys, GLfloat deltaTime);
    void listenMousePicker(Window *window, MousePicker *mousePicker);
    void listenMouseMovement(GLfloat xDelta, GLfloat yDelta);

    glm::vec3 getPosition();
    glm::vec3 getDirection();

    glm::mat4 calculateViewMatrix();

    ~Camera();

private:
    glm::vec3 _position, _front, _up, _right, _worldUp;

    GLfloat _yaw, _pitch;
    GLfloat _movementSpeed, _turnSpeed;

    GLboolean _cursorEnabled;
    GLfloat _resetTime;

    void update();
};
