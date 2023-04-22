#include "Scene.h"

Scene::Scene()
{
    this->_projectionMatrix = glm::mat4(1.0f);
    this->_directionalLight = new DirectionalLight();
    this->_camera = new Camera();
    this->_flashLight = NULL;
    this->_window = NULL;
    this->_directionalLightShader = Shader();
    this->_directionalLightShader.createFromFiles("shaders/directional-shadow-map/shader.vert", "shaders/directional-shadow-map/shader.frag");
}

void Scene::addModel(Model *model)
{
    this->_modelList.push_back(model);
}

void Scene::addModels(std::vector<Model *> models)
{
    for (size_t i = 0; i < models.size(); i++)
    {
        this->_modelList.push_back(models[i]);
    }
}

void Scene::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    this->_projectionMatrix = projectionMatrix;
}

void Scene::setDirectionalLight(DirectionalLight *directionalLight)
{
    this->_directionalLight = directionalLight;
}

void Scene::setFlashLight(FlashLight *flashLight)
{
    this->addSpotLight(flashLight);
    this->_flashLight = flashLight;
}

void Scene::setWindow(Window *window)
{
    this->_window = window;
}

void Scene::addPointLight(PointLight *pointLight)
{
    if (this->_pointLights.size() > MAX_POINT_LIGHTS)
    {
        return;
    }

    this->_pointLights.push_back(pointLight);
}

void Scene::addSpotLight(SpotLight *spotLight)
{
    if (this->_spotLights.size() > MAX_SPOT_LIGHTS)
    {
        return;
    }

    this->_spotLights.push_back(spotLight);
}

void Scene::setCameraPointer(Camera *camera)
{
    this->_camera = camera;
}

void Scene::setDirectionalLightInfo(Shader *shader)
{
    DirectionalLight *directionalLight = this->_directionalLight;

    shader->setUniform3f("directionalLight.base.colour", directionalLight->getColour());
    shader->setUniform1f("directionalLight.base.ambientIntensity", directionalLight->getAmbientIntensity());
    shader->setUniform1f("directionalLight.base.diffuseIntensity", directionalLight->getDiffuseIntensity());
    shader->setUniform3f("directionalLight.direction", directionalLight->getDirection());
}

void Scene::setPointLightsInfo(Shader *shader)
{
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
}

void Scene::setSpotLightsInfo(Shader *shader)
{
    unsigned int spotLightsCount = this->_spotLights.size();
    shader->setUniform1i("spotLightsCount", spotLightsCount);

    for (int i = 0; i < spotLightsCount; i++)
    {
        char buffer[100] = {'\0'};
        SpotLight *spotLight = this->_spotLights[i];

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.base.colour", i);
        shader->setUniform3f(buffer, spotLight->getColour());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.base.ambientIntensity", i);
        shader->setUniform1f(buffer, spotLight->getAmbientIntensity());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.base.diffuseIntensity", i);
        shader->setUniform1f(buffer, spotLight->getDiffuseIntensity());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.position", i);
        shader->setUniform3f(buffer, spotLight->getPosition());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.constant", i);
        shader->setUniform1f(buffer, spotLight->getConstant());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.linear", i);
        shader->setUniform1f(buffer, spotLight->getLinear());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].base.exponent", i);
        shader->setUniform1f(buffer, spotLight->getExponent());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].direction", i);
        shader->setUniform3f(buffer, spotLight->getDirection());

        snprintf(buffer, sizeof(buffer), "spotLights[%d].edge", i);
        shader->setUniform1f(buffer, spotLight->getProcEdge());
    }
}

void Scene::updateFlashLight()
{
    if (this->_flashLight != NULL)
    {
        this->_flashLight->update(this->_camera->getPosition(), this->_camera->getDirection());
    }
}

void Scene::renderPass()
{
    glViewport(0, 0, this->_window->getBufferWidth(), this->_window->getBufferHeight());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<Model *>::iterator itModel;

    this->_directionalLight->getShadowMap()->read(GL_TEXTURE1);

    for (itModel = this->_modelList.begin(); itModel != this->_modelList.end(); ++itModel)
    {
        (*itModel)->prepareToRender();

        Shader *shader = (*itModel)->getShader();

        Material *material = (*itModel)->getMaterial();
        Camera *camera = this->_camera;

        shader->setUniformMatrix4fv("projection", this->_projectionMatrix);
        shader->setUniformMatrix4fv("view", camera->calculateViewMatrix());
        shader->setUniform3f("eyePosition", camera->getPosition());

        // shader->setUniform3f("modelColour", (*itModel)->getColour());
        this->setDirectionalLightInfo(shader);
        this->setPointLightsInfo(shader);
        this->setSpotLightsInfo(shader);
        this->updateFlashLight();

        shader->setUniformMatrix4fv("directionalLightTransform", this->_directionalLight->calculateLightTransform());

        shader->setUniform1i("theTexture", 0);
        shader->setUniform1i("directionalShadowMap", 1);

        shader->setUniformMatrix4fv("model", (*itModel)->getModelMatrix());
        shader->setUniform1f("material.specularIntensity", material->getSpecularIntensity());
        shader->setUniform1f("material.shininess", material->getShininess());

        (*itModel)->render();

        // shader->setUniform3f("modelColour", (*itModel)->getSelectedColour());
        // (*itModel)->renderSelectedMesh();
    }
}

void Scene::shadowMapPass()
{
    this->_directionalLightShader.useShader();

    this->_directionalLightShader.setUniformMatrix4fv("directionalLightTransform",
                                                      this->_directionalLight->calculateLightTransform());

    GLuint shadowWidth = this->_directionalLight->getShadowMap()->getShadowWidth();
    GLuint shadowHeight = this->_directionalLight->getShadowMap()->getShadowHeight();
    glViewport(0, 0, shadowWidth, shadowHeight);

    this->_directionalLight->getShadowMap()->write();

    glClear(GL_DEPTH_BUFFER_BIT);

    std::vector<Model *>::iterator itModel;

    for (itModel = this->_modelList.begin(); itModel != this->_modelList.end(); ++itModel)
    {
        this->_directionalLightShader.setUniformMatrix4fv("model", (*itModel)->getModelMatrix());
        (*itModel)->render();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::render()
{
    this->shadowMapPass();
    this->renderPass();
}

Scene::~Scene()
{
}
