#include "Model.h"

Model::Model(const char *vertexShader,
             const char *fragmentShader,
             const char *texturePath,
             GLfloat *vertices,
             unsigned int *indices,
             unsigned int numOfVertices,
             unsigned int numOfIndices)
{
    this->_shader = new Shader();
    this->_shader->createFromFiles(vertexShader, fragmentShader);

    this->_mesh = new Mesh();
    this->_mesh->createMesh(vertices,
                            indices,
                            numOfVertices,
                            numOfIndices,
                            3,
                            (GLint[]){3, 2, 3},
                            (GLenum[]){GL_FLOAT, GL_FLOAT, GL_FLOAT},
                            8,
                            (unsigned int[]){0, 3, 5});

    this->_texture = new Texture(texturePath);
    this->_texture->loadTexture();
    this->_modelMatrix = glm::mat4(1.0f);
}

Model::Model(const char *vertexShader,
             const char *fragmentShader,
             GLfloat *vertices,
             unsigned int *indices,
             unsigned int numOfVertices,
             unsigned int numOfIndices)
{
    this->_shader = new Shader();
    this->_shader->createFromFiles(vertexShader, fragmentShader);

    this->_mesh = new Mesh();

    this->_mesh->createMesh(vertices,
                            indices,
                            numOfVertices,
                            numOfIndices,
                            1,
                            (GLint[]){3},
                            (GLenum[]){GL_FLOAT},
                            0,
                            (unsigned int[]){0});

    this->_texture = NULL;
    this->_modelMatrix = glm::mat4(1.0f);
}

void Model::setUniformMatrix4fv(const char *uniform, glm::mat4 matrix)
{
    GLuint uniformLocation = this->_shader->getUniformLocation(uniform);
    if (uniformLocation >= 0)
    {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void Model::setUniform3f(const char *uniform, glm::vec3 vec)
{
    GLuint uniformLocation = this->_shader->getUniformLocation(uniform);
    if (uniformLocation >= 0)
    {
        glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
    }
}

void Model::setUniform1f(const char *uniform, GLfloat value)
{
    GLuint uniformLocation = this->_shader->getUniformLocation(uniform);
    if (uniformLocation >= 0)
    {
        glUniform1f(uniformLocation, value);
    }
}

void Model::setModelMatrix(glm::mat4 modelMatrix)
{
    this->_modelMatrix = modelMatrix;
}

glm::mat4 Model::getModelMatrix()
{
    return this->_modelMatrix;
}

void Model::prepareToRender()
{
    if (this->_shader)
    {
        this->useShader();
    }

    if (this->_texture)
    {
        this->useTexture();
    }
}

void Model::useShader()
{
    this->_shader->useShader();
}

void Model::useTexture()
{
    this->_texture->useTexture();
}

void Model::render()
{
    this->_mesh->renderMesh();
}

Model::~Model()
{
    free(this->_shader);
    free(this->_mesh);
    free(this->_texture);
}