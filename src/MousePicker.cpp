#include "MousePicker.h"

MousePicker::MousePicker()
{
}

MousePicker::MousePicker(GLint screenWidth,
                         GLint screenHeight,
                         glm::mat4 projectionMatrix,
                         Geometry geometry)
{
    this->_screenWidth = screenWidth;
    this->_screenHeight = screenHeight;
    this->_projectionMatrix = projectionMatrix;
    this->_geometry = geometry;
    this->_viewMatrix = glm::mat4(1.0f);
}

GLint MousePicker::intersects(glm::vec3 camPos,
                              glm::mat4 camViewMatrix,
                              GLfloat mouseXPos,
                              GLfloat mouseYPos)
{
    this->_viewMatrix = camViewMatrix;

    glm::vec3 rayDirection = this->getMouseToScreenRay(mouseXPos, mouseYPos);
    Ray ray = Ray(camPos, rayDirection);

    GLint indice = -1;
    this->geometryRayIntersection(ray, &indice);

    return indice;
}

GLboolean MousePicker::geometryRayIntersection(Ray ray, int *indice)
{
    GLboolean intersect = false;
    GLfloat minT = FLT_MAX;

    glm::vec3 origin = ray.getOrigin();
    glm::vec3 direction = ray.getDirection();

    for (int i = 0; i < this->_geometry.faces.size(); i++)
    {
        Face face = this->_geometry.faces[i];
        Vertice v0 = this->_geometry.vertices[face.ind0];
        Vertice v1 = this->_geometry.vertices[face.ind1];
        Vertice v2 = this->_geometry.vertices[face.ind2];

        GLfloat newt;
        if (ray.faceIntersection(v0.coords, v1.coords, v2.coords, &newt))
        {
            if (newt < minT)
            {
                minT = newt;
                intersect = true;
                *indice = i;
            }
        }
    }

    return intersect;
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
