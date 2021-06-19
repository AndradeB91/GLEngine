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
#include "Light.h"
#include "Scene.h"

void calcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount,
                        unsigned int vLength, unsigned int normalOffset)
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

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -2.5f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 0.4f, 1.0f));

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f};

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Model *model = new Model(vertexShader,
                             fragmentShader,
                             texturePath,
                             vertices,
                             indices,
                             32,
                             12);

    model->setModelMatrix(modelMatrix);
    return model;

    //     GLfloat vertices[] = {
    //         -1.0f, -1.0f, 0.0f,
    //         0.0f, -1.0f, 1.0f,
    //         1.0f, -1.0f, 0.0f,
    //         0.0f, 1.0f, 0.0f};

    //     Model *model = new Model(vertexShader,
    //                              fragmentShader,
    //                              vertices,
    //                              indices,
    //                              12,
    //                              12);

    //     model->setModelMatrix(modelMatrix);
    //     return model;
}

int main()
{
    GLfloat deltaTime = 0.0f, lastTime = 0.0f;

    Window mainWindow = Window();
    mainWindow.initialize();

    Camera camera = Camera();
    Light light = Light(1.0f, 1.0f, 1.0f, 0.2f,
                        2.0f, -1.0f, -2.0f, 1.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (GLfloat)mainWindow.getBufferWidth() /
                                                mainWindow.getBufferHeight(),
                                            0.1f, 100.0f);

    Scene scene = Scene();
    scene.addModel(createPyramid());
    scene.setProjectionMatrix(projection);
    scene.setLight(light);

    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get and handle user input events
        glfwPollEvents();

        camera.listenKeys(mainWindow.getKeys(), deltaTime);
        camera.listenMouse(mainWindow.getXDelta(), mainWindow.getYDelta());

        scene.setViewMatrix(camera.calculateViewMatrix());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.renderModels();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}