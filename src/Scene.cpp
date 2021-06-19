#include "Scene.h"

Scene::Scene()
{
}

void Scene::addModel(Model *model)
{
    this->_modelList.push_back(model);
}

void Scene::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    this->_projectionMatrix = projectionMatrix;
}

void Scene::setViewMatrix(glm::mat4 viewMatrix)
{
    this->_viewMatrix = viewMatrix;
}

void Scene::setLight(Light light)
{
    this->_light = light;
}

void Scene::renderModels()
{
    std::vector<Model *>::iterator itModel;

    for (itModel = this->_modelList.begin(); itModel != this->_modelList.end(); ++itModel)
    {
        (*itModel)->prepareToRender();

        (*itModel)->setUniformMatrix4fv("model", (*itModel)->getModelMatrix());
        (*itModel)->setUniformMatrix4fv("view", this->_viewMatrix);
        (*itModel)->setUniformMatrix4fv("projection", this->_projectionMatrix);

        (*itModel)->setUniform3f("directionalLight.colour", this->_light.getColour());
        (*itModel)->setUniform1f("directionalLight.ambientIntensity", this->_light.getAmbientIntensity());
        (*itModel)->setUniform3f("directionalLight.direction", this->_light.getDirection());
        (*itModel)->setUniform1f("directionalLight.diffuseIntensity", this->_light.getDiffuseIntensity());

        (*itModel)->render();
    }
}

Scene::~Scene()
{
}
