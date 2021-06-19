#pragma once

#include <vector>
#include <stdio.h>

#include <glm/glm.hpp>

#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "Window.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void addModel(Model *model);

    void setProjectionMatrix(glm::mat4 projectionMatrix);

    void setLight(Light light);
    void setCameraPointer(Camera *camera);

    void render();

private:
    std::vector<Model *> _modelList;

    glm::mat4 _projectionMatrix;

    Light _light;

    Camera *_camera;
};
