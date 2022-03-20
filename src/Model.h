#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Geometry.h"
#include "Texture.h"
#include "Material.h"
#include "Loader.h"

#include <glm/glm.hpp>

class Model
{
public:
      Model();

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

      void setColourPercentage(GLfloat redPercentage, GLfloat greenPercentage, GLfloat bluePercentage);
      void setColourRGB(GLint red, GLint green, GLint blue);

      void setSelectedColourPercentage(GLfloat redPercentage, GLfloat greenPercentage, GLfloat bluePercentage);
      void setSelectedColourRGB(GLint red, GLint green, GLint blue);

      glm::vec3 getColour();
      glm::vec3 getSelectedColour();

      void setMesh(Mesh *mesh);
      Mesh *getMesh();

      void setSelectedMesh(Mesh *mesh);
      Mesh *getSelectedMesh();

      void setGeometry(Geometry *geometry);
      Geometry *getGeometry();

      void buildSelectedMeshGeometry();
      void setSelectedMeshGeometry(Geometry *geometry);
      Geometry *getSelectedMeshGeometry();

      void selectFace(GLint index);

      void updateGeometriesByModelMatrix();

      void setName(const char *name);
      const char *getName();

      void setDoNotRender(bool set);

      void prepareToRender();
      void render();
      void renderSelectedMesh();

private:
      Shader *_shader;

      Mesh *_mesh;
      Mesh *_selectedMesh;

      Geometry *_geometry;
      Geometry *_selectedMeshGeometry;

      Texture *_texture;
      Material *_material;

      glm::mat4 _modelMatrix;

      glm::vec3 _colour, _selectedColour;

      const char *_name;

      bool _doNotRender;
};
