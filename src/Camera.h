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
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        GLfloat yaw = -90.0f,
        GLfloat pitch = 1.0f,
        GLfloat movementSpeed = 3.0f,
        GLfloat turnSpeed = 0.1f);

    void listenKeys(Window *window, bool *keys, GLfloat deltaTime);
    void listenMouseMovement(Window *window, GLfloat xDelta, GLfloat yDelta);
    void listenMousePicker(Window *window, MousePicker mousePicker);

    glm::vec3 getPosition();
    glm::vec3 getDirection();

    glm::mat4 calculateViewMatrix();

    glm::mat4 getOrientation();
    glm::mat4 getView();

    ~Camera();

private:
    glm::vec3 _position, _front, _up, _right, _worldUp;

    GLfloat _yaw, _pitch;
    GLfloat _movementSpeed, _turnSpeed;

    GLboolean _cursorEnabled;
    GLfloat _resetTime;

    void update();
};
