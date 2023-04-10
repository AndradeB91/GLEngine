#include "MousePicker.h"
#include <iostream>

MousePicker::MousePicker()
{
    this->_screenWidth = 800;
    this->_screenHeight = 600;
    this->_projectionMatrix = glm::mat4(1.0f);
    this->_model = new Model();
    this->_viewMatrix = glm::mat4(1.0f);
    this->_selectedFacesIndex = std::list<GLint>();
}

MousePicker::MousePicker(GLint screenWidth,
                         GLint screenHeight,
                         glm::mat4 projectionMatrix,
                         Model *model)
{
    this->_screenWidth = screenWidth;
    this->_screenHeight = screenHeight;
    this->_projectionMatrix = projectionMatrix;
    this->_model = model;
    this->_viewMatrix = glm::mat4(1.0f);
    this->_selectedFacesIndex = std::list<GLint>();
}

std::list<GLint> MousePicker::getSelectedFacesIndexList()
{
    return this->_selectedFacesIndex;
}

void MousePicker::clearSelectedFacesIndexList()
{
    this->_selectedFacesIndex.clear();
}

void MousePicker::intersects(glm::vec3 camPos,
                             glm::mat4 camViewMatrix,
                             GLfloat mouseXPos,
                             GLfloat mouseYPos)
{
    this->_viewMatrix = camViewMatrix;

    glm::vec3 rayDirection = this->getMouseToScreenRay(mouseXPos, mouseYPos);
    Ray ray = Ray(camPos, rayDirection);

    Geometry *geometry = this->_model->getGeometry();
    Geometry *selectedMeshGeometry = this->_model->getSelectedMeshGeometry();

    if (ray.intersectsGeometry(*selectedMeshGeometry))
    {
        return;
    }

    GLint index = -1;
    if (ray.intersectsGeometry(*geometry, &index))
    {
        this->_model->selectFace(index);
    }
}

glm::vec3 MousePicker::getMouseToScreenRay(GLfloat mouseXPos, GLfloat mouseYPos)
{
    glm::vec2 normalizedCoords = this->getNormalizedDeviceCoords(mouseXPos, mouseYPos);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = this->toEyeCoords(clipCoords);
    glm::vec3 worldRay = this->toWorldCoords(eyeCoords);
    return worldRay;
}

glm::vec2 MousePicker::getNormalizedDeviceCoords(GLfloat mouseXPos, GLfloat mouseYPos)
{
    GLfloat x = (2.0f * mouseXPos) / (GLfloat)this->_screenWidth - 1.0f;
    GLfloat y = (2.0f * mouseYPos) / (GLfloat)this->_screenHeight - 1.0f;
    return glm::vec2(x, -y);
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords)
{
    glm::mat4 invertedProjection = glm::inverse(this->_projectionMatrix);
    glm::vec4 eyeCoords = invertedProjection * clipCoords;
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords)
{
    glm::mat4 invertedView = glm::inverse(this->_viewMatrix);
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
    return glm::normalize(mouseRay);
}

MousePicker::~MousePicker()
{
}
