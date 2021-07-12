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
    this->_mesh->build(vertices,
                       indices,
                       numOfVertices,
                       numOfIndices,
                       3,
                       (GLint[]){0, 1, 2},
                       (GLint[]){3, 2, 3},
                       (GLenum[]){GL_FLOAT, GL_FLOAT, GL_FLOAT},
                       8,
                       (unsigned int[]){0, 3, 5});

    this->_texture = new Texture(texturePath);
    this->_texture->loadTextureWithAlpha();
    this->_material = new Material();
    this->_modelMatrix = glm::mat4(1.0f);
    this->_colour = glm::vec3(1.0f, 1.0f, 1.0f);
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

    this->_mesh->build(vertices,
                       indices,
                       numOfVertices,
                       numOfIndices,
                       2,
                       (GLint[]){0, 1},
                       (GLint[]){3, 3},
                       (GLenum[]){GL_FLOAT, GL_FLOAT},
                       6,
                       (unsigned int[]){0, 3});

    this->_texture = NULL;
    this->_material = new Material();
    this->_modelMatrix = glm::mat4(1.0f);
    this->_colour = glm::vec3(1.0f, 1.0f, 1.0f);
}

Model::Model(const char *vertexShader,
             const char *fragmentShader)
{
    this->_shader = new Shader();
    this->_shader->createFromFiles(vertexShader, fragmentShader);
    this->_mesh = new Mesh();
    this->_texture = NULL;
    this->_material = new Material();
    this->_modelMatrix = glm::mat4(1.0f);
    this->_colour = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Model::setModelMatrix(glm::mat4 modelMatrix)
{
    this->_modelMatrix = modelMatrix;
}

glm::mat4 Model::getModelMatrix()
{
    return this->_modelMatrix;
}

void Model::setMaterial(Material *material)
{
    this->_material = material;
}

Material *Model::getMaterial()
{
    return this->_material;
}

void Model::setShader(Shader *shader)
{
    this->_shader = shader;
}

Shader *Model::getShader()
{
    return this->_shader;
}

void Model::setTexture(Texture *texture)
{
    this->_texture = texture;
}

Texture *Model::getTexture()
{
    return this->_texture;
}

void Model::setColourPercentage(GLfloat redPercentage, GLfloat greenPercentage, GLfloat bluePercentage)
{
    this->_colour = glm::vec3(redPercentage, greenPercentage, bluePercentage);
}

void Model::setColourRGB(GLint red, GLint green, GLint blue)
{
    this->_colour = glm::vec3((GLfloat)red / 256.0f,
                              (GLfloat)green / 256.0f,
                              (GLfloat)blue / 256.0f);
}

glm::vec3 Model::getColour()
{
    return this->_colour;
}

void Model::setMesh(Mesh *mesh)
{
    this->_mesh = mesh;
}

Mesh *Model::getMesh()
{
    return this->_mesh;
}

void Model::setGeometry(Geometry geometry)
{
    this->_geometry = geometry;

    for (size_t i = 0; i < this->_geometry.vertices.size(); i++)
    {
        Vertice vertice = this->_geometry.vertices[i];
        glm::vec4 modifiedVertice = this->_modelMatrix * glm::vec4(vertice.coords.x,
                                                                   vertice.coords.y,
                                                                   vertice.coords.z,
                                                                   1.0f);

        this->_geometry.vertices[i] = Vertice(modifiedVertice.x, modifiedVertice.y, modifiedVertice.z);
    }
}

Geometry Model::getGeometry()
{
    return this->_geometry;
}

void Model::prepareToRender()
{
    if (this->_shader != NULL)
    {
        this->_shader->useShader();
    }

    if (this->_texture != NULL)
    {
        this->_texture->useTexture();
    }
}

void Model::render()
{
    this->_mesh->render();
}

Model::~Model()
{
    free(this->_shader);
    free(this->_mesh);
    free(this->_texture);
    free(this->_material);
}