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
#include "SpotLight.h"
#include "FlashLight.h"
#include "Scene.h"
#include "Loader.h"
#include "Geometry.h"
#include "MousePicker.h"

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

// std::vector<Model *> createBlock()
// {
//     static const char *vertexShader = "shaders/coloured-flat/shader.vert";
//     static const char *fragmentShader = "shaders/coloured-flat/shader.frag";

//     Loader loader = Loader();
//     loader.loadObj("objs/block-noised.obj");

//     // Geometry geo = loader.loadObjGeometry("objs/block-noised.obj");
//     // printf("%lu, %lu", geo.getVertices().size(), geo.getFaces().size());

//     std::vector<Model *> modelsList;
//     std::vector<Mesh *> meshList = loader.getMeshList();

//     for (size_t i = 0; i < meshList.size(); i++)
//     {
//         glm::mat4 modelMatrix(1.0f);
//         modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));

//         Model *model = new Model(vertexShader, fragmentShader);

//         model->setMesh(meshList[i]);
//         model->setModelMatrix(modelMatrix);
//         model->setColourRGB(234, 197, 138);

//         modelsList.push_back(model);
//     }

//     return modelsList;
// }

Model *createBlock()
{
    static const char *vertexShader = "shaders/coloured-flat/shader.vert";
    static const char *fragmentShader = "shaders/coloured-flat/shader.frag";

    Loader loader = Loader();
    Geometry geometry = loader.loadObjGeometry("objs/simplex2.obj");

    // for (size_t i = 0; i < 10; i++)
    // {
    //     // geometry.faces.erase(geometry.faces.begin() + i);
    //     geometry.faces.pop_back();
    // }

    Mesh *mesh = loader.geometryToMesh(geometry);

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

    Model *model = new Model(vertexShader, fragmentShader);
    model->setModelMatrix(modelMatrix);
    model->setMesh(mesh);
    model->setGeometry(geometry);
    model->setColourRGB(234, 197, 138);

    return model;
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

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -2.0f, 0.0f));

    Model *model = new Model(vertexShader,
                             fragmentShader,
                             texturePath,
                             vertices,
                             indices,
                             32,
                             6);

    Material *material = new Material(10.0f, 128);

    model->setMaterial(material);
    model->setModelMatrix(modelMatrix);

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
    static const char *vertexShader = "shaders/shader.vert";
    static const char *fragmentShader = "shaders/shader.frag";
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
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -2.5f));

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
    GLint screenWidth = 768;
    GLint screenHeight = 768;
    Window mainWindow = Window(screenWidth, screenHeight);
    mainWindow.initialize();

    Camera camera = Camera();

    DirectionalLight *directionalLight = new DirectionalLight(1.0f, 1.0f, 1.0f,
                                                              0.2f, 0.7f,
                                                              -3.0f, -3.0f, -3.0f);

    PointLight *pointLight1 = new PointLight(1.0f, 1.0f, 1.0f,
                                             0.1f, 0.7f,
                                             -4.0f, 2.0f, 0.0f,
                                             0.8f, 0.2f, 0.1f);

    PointLight *pointLight2 = new PointLight(0.5f, 0.0f, 1.0f,
                                             0.01f, 1.0f,
                                             4.0f, 2.0f, 0.0f,
                                             0.3f, 0.2f, 0.1f);

    PointLight *pointLight3 = new PointLight(0.0f, 0.0f, 1.0f,
                                             0.01f, 1.0f,
                                             0.0f, 2.0f, -10.0f,
                                             0.3f, 0.2f, 0.1f);

    FlashLight *flashLight = new FlashLight(0.8f, 0.8f, 0.8f,
                                            0.0f, 2.0f,
                                            0.0f, 0.0f, 0.0f,
                                            0.0f, -1.0f, 0.0f,
                                            1.0f, 0.0f, 0.0f,
                                            200.0f);

    SpotLight *spotLight2 = new SpotLight(1.0f, 1.0f, 1.0f,
                                          0.0f, 0.5f,
                                          0.0f, 10.0f, 0.0f,
                                          0.0f, -1.0f, 0.0f,
                                          1.0f, 0.0f, 0.0f,
                                          10.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),
                                            0.1f,
                                            100.0f);
    Model *block = createBlock();

    Scene scene = Scene();
    scene.addModel(createFloor());
    scene.addModel(block);
    scene.setProjectionMatrix(projection);
    scene.setDirectionalLight(directionalLight);
    scene.setCameraPointer(&camera);

    MousePicker mousePicker = MousePicker(screenWidth,
                                          screenHeight,
                                          projection,
                                          block->getGeometry());

    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get and handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.listenKeys(&mainWindow, mainWindow.getKeys(), deltaTime);
        camera.listenMouseMovement(&mainWindow, mainWindow.getXDelta(), mainWindow.getYDelta());
        camera.listenMousePicker(&mainWindow, mousePicker);

        directionalLight->setDirection(camera.getDirection());

        scene.render();

        mainWindow.swapBuffers();
    }

    return 0;
}