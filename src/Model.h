#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model
{
public:
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

    void setUniformMatrix4fv(const char *uniform, glm::mat4 matrix);
    void setUniform3f(const char *uniform, glm::vec3 vec);
    void useShader();
    void useTexture();
    void prepareToRender();
    void render();

private:
    Shader *_shader;
    Mesh *_mesh;
    Texture *_texture;
};
