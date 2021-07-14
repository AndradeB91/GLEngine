#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>

#include "Model.h"
#include "Ray.h"

class MousePicker
{

public:
    MousePicker();

    MousePicker(GLint screenWidth,
                GLint screenHeight,
                glm::mat4 projectionMatrix,
                Model *model);

    void intersects(glm::vec3 camPos,
                    glm::mat4 camViewMatrix,
                    GLfloat mouseXPos,
                    GLfloat mouseYPos);

    std::list<GLint> getSelectedFacesIndexList();
    void clearSelectedFacesIndexList();

    ~MousePicker();

private:
    glm::vec3 getMouseToScreenRay(GLfloat mouseXPos, GLfloat mouseYPos);
    glm::vec2 getNormalizedDeviceCoords(GLfloat mouseXPos, GLfloat mouseYPos);
    glm::vec4 toEyeCoords(glm::vec4 clipCoords);
    glm::vec3 toWorldCoords(glm::vec4 eyeCoords);

    void addUniqueIndexToList(GLint index);

    GLint _screenWidth, _screenHeight;

    glm::mat4 _projectionMatrix, _viewMatrix;

    Model _model;

    std::list<GLint> _selectedFacesIndex;
};
