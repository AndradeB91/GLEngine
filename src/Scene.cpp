#include "Scene.h"

Scene::Scene()
{
    this->_projectionMatrix = glm::mat4(1.0f);
    this->_directionalLight = DirectionalLight();
    this->_pointLightsCount = 0;
    this->_camera = new Camera();
}

void Scene::addModel(Model *model)
{
    this->_modelList.push_back(model);
}

void Scene::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    this->_projectionMatrix = projectionMatrix;
}

void Scene::setDirectionalLight(DirectionalLight directionalLight)
{
    this->_directionalLight = directionalLight;
}

void Scene::addPointLight(PointLight pointLight)
{
    if (this->_pointLights.size() > MAX_POINT_LIGHTS)
    {
        return;
    }

    this->_pointLights.push_back(&pointLight);
}

void Scene::setCameraPointer(Camera *camera)
{
    this->_camera = camera;
}

void Scene::render()
{
    std::vector<Model *>::iterator itModel;

    for (itModel = this->_modelList.begin(); itModel != this->_modelList.end(); ++itModel)
    {
        (*itModel)->prepareToRender();

        Shader *shader = (*itModel)->getShader();
        Material *material = (*itModel)->getMaterial();
        Camera *camera = this->_camera;
        DirectionalLight directionalLight = this->_directionalLight;

        shader->setUniformMatrix4fv("model", (*itModel)->getModelMatrix());
        shader->setUniformMatrix4fv("projection", this->_projectionMatrix);
        shader->setUniformMatrix4fv("view", camera->calculateViewMatrix());
        shader->setUniform3f("eyePosition", camera->getPosition());

        shader->setUniform1f("material.specularIntensity", material->getSpecularIntensity());
        shader->setUniform1f("material.shininess", material->getShininess());

        shader->setUniform3f("directionalLight.base.colour", directionalLight.getColour());
        shader->setUniform1f("directionalLight.base.ambientIntensity", directionalLight.getAmbientIntensity());
        shader->setUniform1f("directionalLight.base.diffuseIntensity", directionalLight.getDiffuseIntensity());
        shader->setUniform3f("directionalLight.direction", directionalLight.getDirection());

        unsigned int pointLightsCount = this->_pointLights.size();
        shader->setUniform1i("pointLightsCount", pointLightsCount);

        for (int i = 0; i < pointLightsCount; i++)
        {
            char buffer[100] = {'\0'};
            PointLight *pointLight = this->_pointLights[i];

            snprintf(buffer, sizeof(buffer), "pointLights[%d].base.colour", i);
            shader->setUniform3f(buffer, pointLight->getColour());

            snprintf(buffer, sizeof(buffer), "pointLights[%d].base.ambientIntensity", i);
            shader->setUniform1f(buffer, pointLight->getAmbientIntensity());

            snprintf(buffer, sizeof(buffer), "pointLights[%d].base.diffuseIntensity", i);
            shader->setUniform1f(buffer, pointLight->getDiffuseIntensity());

            snprintf(buffer, sizeof(buffer), "pointLights[%d].position", i);
            shader->setUniform3f(buffer, pointLight->getPosition());

            snprintf(buffer, sizeof(buffer), "pointLights[%d].constant", i);
            shader->setUniform1f(buffer, pointLight->getConstant());

            snprintf(buffer, sizeof(buffer), "pointLights[%d].linear", i);
            shader->setUniform1f(buffer, pointLight->getLinear());

            snprintf(buffer, sizeof(buffer), "pointLights[%d].exponent", i);
            shader->setUniform1f(buffer, pointLight->getExponent());
        }

        (*itModel)->render();
    }
}

Scene::~Scene()
{
}
