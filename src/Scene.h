#pragma once

#include <vector>
#include <stdio.h>

#include <glm/glm.hpp>

#include "Model.h"
#include "Camera.h"
#include "Window.h"
#include "Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"

const unsigned int MAX_POINT_LIGHTS = 3;

class Scene
{
public:
    Scene();
    ~Scene();

    void addModel(Model *model);

    void setProjectionMatrix(glm::mat4 projectionMatrix);

    void setDirectionalLight(DirectionalLight directionalLight);
    void addPointLight(PointLight pointLight);

    void setCameraPointer(Camera *camera);

    void render();

private:
    std::vector<Model *> _modelList;

    glm::mat4 _projectionMatrix;

    DirectionalLight _directionalLight;

    unsigned int _pointLightsCount;

    std::vector<PointLight *> _pointLights;

    Camera *_camera;
};
