#pragma once

#include <vector>
#include <stdio.h>

#include <glm/glm.hpp>

#include "Model.h"
#include "Light.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void addModel(Model *model);

    void setProjectionMatrix(glm::mat4 projectionMatrix);
    void setViewMatrix(glm::mat4 viewMatrix);

    void setLight(Light light);

    void renderModels();

private:
    std::vector<Model *> _modelList;

    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;

    Light _light;
};
