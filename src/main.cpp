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
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f};

    return new Model(vertexShader,
                     fragmentShader,
                     texturePath,
                     vertices,
                     indices,
                     20,
                     12);

    // GLfloat vertices[] = {
    //     -1.0f, -1.0f, 0.0f,
    //     0.0f, -1.0f, 1.0f,
    //     1.0f, -1.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f};

    // return new Model(vertexShader,
    //                  fragmentShader,
    //                  vertices,
    //                  indices,
    //                  12,
    //                  12);
}

int main()
{
    GLfloat deltaTime = 0.0f, lastTime = 0.0f;

    Window mainWindow = Window();
    mainWindow.initialize();

    Camera camera = Camera();

    std::vector<Model *> modelList;
    std::vector<Model *>::iterator itModel;

    modelList.push_back(createPyramid());

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),
                                            0.1f, 100.0f);

    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get and handle user input events
        glfwPollEvents();

        camera.listenKeys(mainWindow.getKeys(), deltaTime);
        camera.listenMouse(mainWindow.getXDelta(), mainWindow.getYDelta());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (itModel = modelList.begin(); itModel != modelList.end(); ++itModel)
        {
            (*itModel)->prepareToRender();

            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

            glm::mat4 view = camera.calculateViewMatrix();

            (*itModel)->setMatrix("model", model);
            (*itModel)->setMatrix("view", view);
            (*itModel)->setMatrix("projection", projection);

            (*itModel)->render();
        }

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}