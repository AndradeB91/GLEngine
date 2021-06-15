#include "Shader.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model
{
public:
    Model(const char *vertexShader, const char *fragmentShader,
          GLfloat *vertices, unsigned int *indices,
          unsigned int numOfVertices, unsigned int numOfIndices);
    ~Model();

    void setMatrix(const char *uniform, glm::mat4 matrix);
    void useShader();
    void render();

private:
    Shader *_shader;
    Mesh *_mesh;
};
