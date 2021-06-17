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
    this->_mesh->createMesh(vertices, indices, numOfVertices, numOfIndices);

    if (texturePath)
    {
        this->_texture = new Texture(texturePath);
        this->_texture->loadTexture();
    }
}

void Model::setMatrix(const char *uniform, glm::mat4 matrix)
{
    GLuint uniformLocation = this->_shader->getUniformLocation(uniform);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
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
}