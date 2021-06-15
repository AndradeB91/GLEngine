#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat turnSpeed)
{
  this->_position = position;
  this->_worldUp = up;
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

void Camera::update()
{
  this->_front.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
  this->_front.y = sin(glm::radians(this->_pitch));
  this->_front.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
  this->_front = glm::normalize(this->_front);

  this->_right = glm::normalize(glm::cross(this->_front, this->_worldUp));

  this->_up = glm::normalize(glm::cross(this->_right, this->_front));
}

void Camera::listenKeys(bool *keys, GLfloat deltaTime)
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

  if (keys[GLFW_KEY_LEFT_CONTROL])
  {
    this->_position -= this->_up * velocity;
  }

  if (keys[GLFW_KEY_SPACE])
  {
    this->_position += this->_up * velocity;
  }
}

void Camera::listenMouse(GLfloat xDelta, GLfloat yDelta)
{
  xDelta *= this->_turnSpeed;
  yDelta *= this->_turnSpeed;

  this->_yaw += xDelta;
  this->_pitch = std::min(this->_pitch + yDelta, 89.9f);

  this->update();
}

Camera::~Camera()
{
}
