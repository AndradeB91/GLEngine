#pragma once

#include "Model.h"

#include "MshSurfDriver.h"

// vendor
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw_gl3.h"

class Gui
{
public:
    Gui();

    Gui(GLFWwindow *window);

    void render();

    void setModel(Model *model);

    ~Gui();

private:
    Model *_model;

    ImVec4 _modelColour, _selectionColour;

    float _materialIntensity;
    int _materialShininessFactor;

    float _triangleQualityFactor;
    float _maxElementSize;

    MshSurfDriver _driver;
};
