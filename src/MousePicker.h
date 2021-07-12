#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Geometry.h"
#include "Ray.h"

class MousePicker
{

public:
    MousePicker();

    MousePicker(GLint screenWidth,
                GLint screenHeight,
                glm::mat4 projectionMatrix,
                Geometry geometry);

    GLint intersects(glm::vec3 camPos,
                     glm::mat4 camViewMatrix,
                     GLfloat mouseXPos,
                     GLfloat mouseYPos);

    ~MousePicker();

private:
    GLboolean geometryRayIntersection(Ray ray, int *indice);

    glm::vec3 getMouseToScreenRay(GLfloat mouseXPos, GLfloat mouseYPos);
    glm::vec2 getNormalizedDeviceCoords(GLfloat mouseXPos, GLfloat mouseYPos);
    glm::vec4 toEyeCoords(glm::vec4 clipCoords);
    glm::vec3 toWorldCoords(glm::vec4 eyeCoords);

    GLint _screenWidth, _screenHeight;
    glm::mat4 _projectionMatrix, _viewMatrix;
    Geometry _geometry;
};
