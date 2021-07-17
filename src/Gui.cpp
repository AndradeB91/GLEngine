#include "Gui.h"

Gui::Gui()
{
}

bool show_demo_window = true;
bool show_another_window = false;
bool config_window = true;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

Gui::Gui(GLFWwindow *window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
}

void Gui::setModel(Model *model)
{
    this->_model = model;

    glm::vec3 modelColour = this->_model->getColour();
    this->_modelColour = ImVec4(modelColour.x, modelColour.y, modelColour.z, 1.00f);
    glm::vec3 selectionColour = this->_model->getSelectedColour();
    this->_selectionColour = ImVec4(selectionColour.x, selectionColour.y, selectionColour.z, 1.00f);

    Material *modelMaterial = this->_model->getMaterial();
    this->_materialIntensity = modelMaterial->getSpecularIntensity();
    this->_materialShininessFactor = modelMaterial->getShininessFactor();
}

void Gui::render()
{
    ImGui_ImplGlfwGL3_NewFrame();

    {
        ImGui::Begin("Configuration", &config_window, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                { /* Do stuff */
                }
                if (ImGui::MenuItem("Close", "Ctrl+W"))
                {
                    config_window = false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Text("Model: %s\n", this->_model->getName());

        ImGui::ColorEdit3("Model Colour\n", (float *)&this->_modelColour);
        this->_model->setColourPercentage(this->_modelColour.x, this->_modelColour.y, this->_modelColour.z);

        ImGui::ColorEdit3("Selection Colour\n", (float *)&this->_selectionColour);
        this->_model->setSelectedColourPercentage(this->_selectionColour.x, this->_selectionColour.y, this->_selectionColour.z);

        ImGui::SliderFloat("Mat. Intensity", &this->_materialIntensity, 0.0f, 10.0f);
        ImGui::SliderInt("Mat. Shininess", &this->_materialShininessFactor, 0, 20);

        this->_model->setMaterial(new Material(this->_materialIntensity,
                                               this->_materialShininessFactor));

        // printf("second: %f\n", this->_model->getGeometry().vertices[0].coords.x);
        // static float f = 0.0f;
        // static int counter = 0;
        // ImGui::Text("\nApplication average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
        // ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

        // ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our windows open/close state
        // ImGui::Checkbox("Another Window", &show_another_window);

        // if (ImGui::Button("Button")) // Buttons return true when clicked (NB: most widgets return true when edited/activated)
        //     counter++;
        // ImGui::SameLine();
        // ImGui::Text("counter = %d", counter);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

Gui::~Gui()
{
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
}
