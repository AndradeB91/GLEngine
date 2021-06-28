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
#include "SpotLight.h"
#include "FlashLight.h"

const unsigned int MAX_POINT_LIGHTS = 10;
const unsigned int MAX_SPOT_LIGHTS = 10;

class Scene
{
public:
    Scene();
    ~Scene();

    void addModel(Model *model);
    void addModels(std::vector<Model *> models);

    void setProjectionMatrix(glm::mat4 projectionMatrix);

    void setDirectionalLight(DirectionalLight *directionalLight);
    void setFlashLight(FlashLight *flashLight);
    void addPointLight(PointLight *pointLight);
    void addSpotLight(SpotLight *spotLight);

    void setCameraPointer(Camera *camera);

    void render();

private:
    std::vector<Model *> _modelList;

    glm::mat4 _projectionMatrix;

    DirectionalLight *_directionalLight;
    FlashLight *_flashLight;
    std::vector<PointLight *> _pointLights;
    std::vector<SpotLight *> _spotLights;

    Camera *_camera;

    void renderDirectionalLight(Shader *shader);
    void renderPointLights(Shader *shader);
    void renderSpotLights(Shader *shader);
    void updateFlashLight();
};
