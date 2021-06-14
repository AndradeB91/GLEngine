#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

void createObjects(std::vector<Mesh *> *meshList)
{
	unsigned int indices[] = {
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2};

	GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f};

	Mesh *obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 12, 12);
	meshList->push_back(obj1);
}

void createShaders(std::vector<Shader> *shaderList)
{
	static const char *vShader = "shaders/shader.vert";
	static const char *fShader = "shaders/shader.frag";

	Shader *shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList->push_back(*shader1);
}

int main()
{
	Window mainWindow = Window(1024, 768);
	mainWindow.initialize();

	std::vector<Mesh *> meshList;
	std::vector<Mesh *>::iterator mesh;
	std::vector<Shader> shaderList;

	createObjects(&meshList);
	createShaders(&shaderList);

	GLuint uniformProjection = 0, uniformModel = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		// Get and handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (mesh = meshList.begin(); mesh != meshList.end(); ++mesh)
		{
			shaderList[0].useShader();
			uniformModel = shaderList[0].getUniformLocation("model");
			uniformProjection = shaderList[0].getUniformLocation("projection");

			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

			(*mesh)->renderMesh();
		}

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}