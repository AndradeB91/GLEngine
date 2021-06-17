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
                            2,
                            (GLint[]){3, 2},
                            (GLenum[]){GL_FLOAT, GL_FLOAT},
                            5,
                            (unsigned int[]){0, 3});

    this->_texture = new Texture(texturePath);
    this->_texture->loadTexture();
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
}

void Model::setMatrix(const char *uniform, glm::mat4 matrix)
{
    GLuint uniformLocation = this->_shader->getUniformLocation(uniform);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
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