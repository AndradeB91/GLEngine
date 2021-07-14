#include "Camera.h"

const float RESET_TIME_MAX = 1.0f;
const float RESET_TIME_STEP = 0.05f;
const float MAX_ANGLE = 89.0f;

Camera::Camera(GLfloat xPos,
               GLfloat yPos,
               GLfloat zPos,
               GLfloat xUp,
               GLfloat yUp,
               GLfloat zUp,
               GLfloat yaw,
               GLfloat pitch,
               GLfloat movementSpeed,
               GLfloat turnSpeed)
{
    this->_cursorEnabled = true;
    this->_resetTime = 0.0f;
    this->_position = glm::vec3(xPos, yPos, zPos);
    this->_worldUp = glm::vec3(xUp, yUp, zUp);
    this->_yaw = yaw;
    this->_pitch = pitch;
    this->_front = glm::vec3(0.0f, 0.0f, -1.0f);

    this->_movementSpeed = movementSpeed;
    this->_turnSpeed = turnSpeed;

    this->update();
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(this->_position, this->_position + this->_front, this->_up);
}

glm::vec3 Camera::getPosition()
{
    return this->_position;
}

glm::vec3 Camera::getDirection()
{
    return glm::normalize(this->_front);
}

void Camera::update()
{
    this->_front.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    this->_front.y = sin(glm::radians(this->_pitch));
    this->_front.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    this->_front = glm::normalize(this->_front);

    this->_right = glm::normalize(glm::cross(this->_front, this->_worldUp));

    this->_up = glm::normalize(glm::cross(this->_right, this->_front));

    this->_resetTime = std::max(0.0f, this->_resetTime - RESET_TIME_STEP);
}

void Camera::listenKeys(Window *window, bool *keys, GLfloat deltaTime)
{
    GLfloat velocity = this->_movementSpeed * deltaTime;

    if (keys[GLFW_KEY_W])
    {
        this->_position += this->_front * velocity;
    }

    if (keys[GLFW_KEY_S])
    {
        this->_position -= this->_front * velocity;
    }

    if (keys[GLFW_KEY_D])
    {
        this->_position += this->_right * velocity;
    }

    if (keys[GLFW_KEY_A])
    {
        this->_position -= this->_right * velocity;
    }

    if (keys[GLFW_KEY_LEFT_SHIFT])
    {
        this->_position -= this->_up * velocity;
    }

    if (keys[GLFW_KEY_SPACE])
    {
        this->_position += this->_up * velocity;
    }

    if (keys[GLFW_KEY_EQUAL])
    {
        this->_movementSpeed += 0.2f;
    }

    if (keys[GLFW_KEY_MINUS])
    {
        this->_movementSpeed = std::max(0.1f, this->_movementSpeed - 0.2f);
    }

    if (keys[GLFW_KEY_TAB] && this->_resetTime == 0.0f)
    {
        if (this->_cursorEnabled)
        {
            glfwSetInputMode(window->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            this->_turnSpeed = 0.1f;
        }
        else
        {
            glfwSetInputMode(window->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            glfwSetCursorPos(window->getWindowPointer(),
                             window->getWidth() / 2.0f,
                             window->getHeight() / 2.0f);

            this->_turnSpeed = 0;
        }

        this->_resetTime = RESET_TIME_MAX;
        this->_cursorEnabled = !this->_cursorEnabled;
    }
}

void Camera::listenMouseMovement(GLfloat xDelta, GLfloat yDelta)
{
    xDelta *= this->_turnSpeed;
    yDelta *= this->_turnSpeed;

    this->_yaw += xDelta;

    this->_pitch += yDelta;

    if (this->_pitch > MAX_ANGLE)
    {
        this->_pitch = MAX_ANGLE;
    }

    if (this->_pitch < -MAX_ANGLE)
    {
        this->_pitch = -MAX_ANGLE;
    }

    this->update();
}

void Camera::listenMousePicker(Window *window, MousePicker *mousePicker)
{
    if (this->_cursorEnabled &&
        this->_resetTime == 0.0f &&
        glfwGetMouseButton(window->getWindowPointer(), GLFW_MOUSE_BUTTON_1))
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window->getWindowPointer(), &mouseX, &mouseY);

        mousePicker->intersects(this->_position,
                                this->calculateViewMatrix(),
                                (GLfloat)mouseX, (GLfloat)mouseY);

        printf("%lu\n", mousePicker->getSelectedFacesIndexList().size());

        this->_resetTime = RESET_TIME_MAX;
    }
}

Camera::~Camera()
{
}
