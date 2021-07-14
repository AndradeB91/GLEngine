#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Geometry.h"
#include "Texture.h"
#include "Material.h"

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

      void setScaleFactor(GLfloat scaleFactor);
      GLfloat getScaleFactor();

      void setMaterial(Material *material);
      Material *getMaterial();

      void setShader(Shader *shader);
      Shader *getShader();

      void setTexture(Texture *texture);
      Texture *getTexture();

      void setColourPercentage(GLfloat redPercentage, GLfloat greenPercentage, GLfloat bluePercentage);
      void setColourRGB(GLint red, GLint green, GLint blue);

      glm::vec3 getColour();

      void setMesh(Mesh *mesh);
      Mesh *getMesh();

      void setGeometry(Geometry geometry);
      Geometry getGeometry();

      void updateGeometryByModelMatrix();

      void setName(const char *name);
      const char *getName();

      void prepareToRender();
      void render();

private:
      Shader *_shader;
      Mesh *_mesh;
      Geometry _geometry;
      Texture *_texture;
      Material *_material;
      glm::mat4 _modelMatrix;
      GLfloat _scaleFactor;
      glm::vec3 _colour;
      const char *_name;
};
