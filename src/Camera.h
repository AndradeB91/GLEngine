#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        GLfloat yaw = -90.0f,
        GLfloat pitch = 1.0f,
        GLfloat movementSpeed = 5.0f,
        GLfloat turnSpeed = 0.1f);

    void listenKeys(bool *keys, GLfloat deltaTime);
    void listenMouse(GLfloat xDelta, GLfloat yDelta);

    glm::mat4 calculateViewMatrix();

    ~Camera();

private:
    glm::vec3 _position, _front, _up, _right, _worldUp;

    GLfloat _yaw, _pitch;
    GLfloat _movementSpeed, _turnSpeed;

    void update();
};
