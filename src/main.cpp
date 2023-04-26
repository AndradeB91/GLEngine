#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "FlashLight.h"
#include "Scene.h"
#include "Loader.h"
#include "Geometry.h"
#include "MousePicker.h"
#include "Gui.h"

void calcAverageNormals(unsigned int *indices,
                        unsigned int indiceCount,
                        GLfloat *vertices,
                        unsigned int verticeCount,
                        unsigned int vLength,
                        unsigned int normalOffset)
{
    for (size_t i = 0; i < indiceCount; i += 3)
    {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;
        vertices[in0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
    }
}

Model *createBlock()
{
    static const char *vertexShader = "shaders/coloured-flat/shader.vert";
    static const char *fragmentShader = "shaders/coloured-flat/shader.frag";

    Loader loader = Loader();
    Geometry *geometry = loader.loadObjGeometry("objs/block-noised.obj");

    glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.06f, 0.06f, 0.06f));

    Model *model = new Model(vertexShader, fragmentShader);
    model->setName("block.obj");

    model->setModelMatrix(modelMatrix);

    Mesh *mesh = loader.geometryToMesh(geometry);
    model->setMesh(mesh);

    model->setGeometry(geometry);
    model->buildSelectedMeshGeometry();
    model->updateGeometriesByModelMatrix();

    model->setColourRGB(234, 197, 138);
    model->setSelectedColourRGB(255, 0, 0);
    model->setMaterial(new Material(0.18f, 8));

    return model;
}

std::vector<Model *> createXWing()
{
    static const char *vertexShader = "shaders/textured/shader.vert";
    static const char *fragmentShader = "shaders/textured/shader.frag";

    Loader loader = Loader();
    loader.loadObj("objs/x-wing.obj");

    std::vector<Model *> modelsList;

    std::vector<Mesh *> meshList = loader.getMeshList();
    std::vector<Texture *> textureList = loader.getTextureList();
    std::vector<unsigned int> meshToTex = loader.getMeshToTex();

    for (size_t i = 0; i < meshList.size(); i++)
    {
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.0f, 0.5f, 8.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.006f, 0.006f, 0.006f));

        Model *model = new Model(vertexShader, fragmentShader);
        unsigned int materialIndex = meshToTex[i];
        model->setTexture(textureList[materialIndex]);
        model->setMesh(meshList[i]);
        model->setModelMatrix(modelMatrix);

        modelsList.push_back(model);
    }

    return modelsList;
}

std::vector<Model *> createCat()
{
    static const char *vertexShader = "shaders/textured/shader.vert";
    static const char *fragmentShader = "shaders/textured/shader.frag";

    Loader loader = Loader();
    loader.loadObj("objs/cat.obj");

    std::vector<Model *> modelsList;

    std::vector<Mesh *> meshList = loader.getMeshList();
    std::vector<Texture *> textureList = loader.getTextureList();
    std::vector<unsigned int> meshToTex = loader.getMeshToTex();

    for (size_t i = 0; i < meshList.size(); i++)
    {
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.04f, 0.04f));

        Model *model = new Model(vertexShader, fragmentShader);
        unsigned int materialIndex = meshToTex[i];
        model->setTexture(textureList[materialIndex]);
        model->setMesh(meshList[i]);
        model->setModelMatrix(modelMatrix);

        modelsList.push_back(model);
    }

    return modelsList;
}
Model *createFloor()
{
    static const char *vertexShader = "shaders/textured/shader.vert";
    static const char *fragmentShader = "shaders/textured/shader.frag";
    static const char *texturePath = "textures/dirt.png";

    unsigned int indices[] = {
        0, 2, 1,
        1, 2, 3};

    GLfloat vertices[] = {
        -10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -10.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, -1.0f, 0.0f};

    Model *model = new Model(vertexShader,
                             fragmentShader,
                             texturePath,
                             vertices,
                             indices,
                             32,
                             6);

    model->setMaterial(new Material(1.0f, 7));

    return model;
}

Model *createPyramidWithoutTexture()
{
    static const char *vertexShader = "shaders/coloured/shader.vert";
    static const char *fragmentShader = "shaders/coloured/shader.frag";

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -2.5f));

    Material *material = new Material(1.0f, 2);

    calcAverageNormals(indices, 12, vertices, 24, 6, 3);

    Model *model = new Model(vertexShader,
                             fragmentShader,
                             vertices,
                             indices,
                             24,
                             12);

    model->setModelMatrix(modelMatrix);
    model->setMaterial(material);
    model->setColourPercentage(0.8f, 0.8f, 0.8f);

    return model;
}

Model *createPyramid()
{
    static const char *vertexShader = "shaders/textured/shader.vert";
    static const char *fragmentShader = "shaders/textured/shader.frag";
    static const char *texturePath = "textures/brick.png";

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f};

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.0f, 0.0f));

    Material *material = new Material(1.0f, 32);

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Model *model = new Model(vertexShader,
                             fragmentShader,
                             texturePath,
                             vertices,
                             indices,
                             32,
                             12);

    model->setModelMatrix(modelMatrix);
    model->setMaterial(material);

    return model;
}

int main()
{
    GLfloat deltaTime = 0.0f, lastTime = 0.0f;

    glm::vec2 SCREEN(1280, 768);
    Window mainWindow = Window(SCREEN.x, SCREEN.y);
    mainWindow.initialize();

    Camera camera = Camera(2.0f, 2.0f, 2.0f,
                           0.0f, 1.0f, 0.0f,
                           -135.0f, -25.0f,
                           3.0f,
                           0.1f);

    PointLight *p1 = new PointLight(1.0f, 1.0f, 1.0f,
                                    0.01f, 1.0f,
                                    2.0f, 1.0f, 2.0f,
                                    0.8f, 0.2f, 0.1f);

    PointLight *p2 = new PointLight(0.0f, 1.0f, 0.0f,
                                    0.01f, 1.0f,
                                    -2.0f, 1.0f, 2.0f,
                                    0.8f, 0.2f, 0.1f);

    PointLight *p3 = new PointLight(0.0f, 0.0f, 1.0f,
                                    0.01f, 1.0f,
                                    2.0f, 1.0f, -2.0f,
                                    0.8f, 0.2f, 0.1f);

    PointLight *p4 = new PointLight(1.0f, 0.0f, 0.0f,
                                    0.01f, 1.0f,
                                    -2.0f, 1.0f, -2.0f,
                                    0.8f, 0.2f, 0.1f);

    DirectionalLight *directionalLight = new DirectionalLight(1.0f, 1.0f, 1.0f,
                                                              0.2f, 1.0f,
                                                              -20.0f, -15.0f, -10.0f,
                                                              4000, 4000);

    FlashLight *flashLight = new FlashLight(1.0f, 1.0f, 1.0f,
                                            0.5f, 0.4f,
                                            0.0f, 0.0f, 0.0f,
                                            0.0f, -1.0f, 0.0f,
                                            1.0f, 0.0f, 0.0f,
                                            20.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),
                                            0.01f,
                                            100.0f);
    Model *block = createBlock();
    Model *floor = createFloor();

    Scene scene = Scene();

    scene.setWindow(&mainWindow);

    scene.addModel(floor);
    // scene.addModels(createXWing());
    scene.addModels(createCat());
    // scene.addModel(block);
    // scene.addModel(createPyramid());

    scene.setProjectionMatrix(projection);

    scene.addPointLight(p1);
    scene.addPointLight(p2);
    scene.addPointLight(p3);
    scene.addPointLight(p4);

    // scene.setFlashLight(flashLight);
    scene.setDirectionalLight(directionalLight);

    scene.setCameraPointer(&camera);

    MousePicker mousePicker = MousePicker(SCREEN.x, SCREEN.y, projection, block);

    // Gui interface = Gui(mainWindow.getWindowPointer());
    // interface.setModel(block);

    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get and handle user input events
        glfwPollEvents();

        camera.listenKeys(&mainWindow, deltaTime);
        camera.listenMousePicker(&mainWindow, &mousePicker);
        camera.listenMouseMovement(mainWindow.getXDelta(), mainWindow.getYDelta());

        scene.render();
        // interface.render();

        mainWindow.swapBuffers();
    }

    return 0;
}