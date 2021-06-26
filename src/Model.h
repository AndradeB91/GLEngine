#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

#include <glm/glm.hpp>

class Model
{
public:
    Model(const char *vertexShader,
          const char *fragmentShader);

    Model(const char *vertexShader,
          const char *fragmentShader,
          const char *texturePath,
          GLfloat *vertices,
          unsigned int *indices,
          unsigned int numOfVertices,
          unsigned int numOfIndices);

    Model(const char *vertexShader,
          const char *fragmentShader,
          GLfloat *vertices,
          unsigned int *indices,
          unsigned int numOfVertices,
          unsigned int numOfIndices);

    ~Model();

    void setModelMatrix(glm::mat4 modelMatrix);
    glm::mat4 getModelMatrix();

    void setMaterial(Material *material);
    Material *getMaterial();

    void setShader(Shader *shader);
    Shader *getShader();

    void setTexture(Texture *texture);
    Texture *getTexture();

    void setColour(GLfloat red, GLfloat green, GLfloat blue);
    glm::vec3 getColour();

    void setMesh(Mesh *mesh);
    Mesh *getMesh();

    void prepareToRender();
    void render();

private:
    Shader *_shader;
    Mesh *_mesh;
    Texture *_texture;
    Material *_material;
    glm::mat4 _modelMatrix;
    glm::vec3 _colour;
};
