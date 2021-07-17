#include "Model.h"

Model::Model()
{
}

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

    this->_selectedMesh = new Mesh();
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

    this->_geometry = new Geometry();
    this->_selectedMeshGeometry = new Geometry();

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

    this->_selectedMesh = new Mesh();
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

    this->_geometry = new Geometry();
    this->_selectedMeshGeometry = new Geometry();

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
    this->_selectedMesh = new Mesh();

    this->_geometry = new Geometry();
    this->_selectedMeshGeometry = new Geometry();

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

void Model::setSelectedColourPercentage(GLfloat redPercentage, GLfloat greenPercentage, GLfloat bluePercentage)
{
    this->_selectedColour = glm::vec3(redPercentage, greenPercentage, bluePercentage);
}

void Model::setSelectedColourRGB(GLint red, GLint green, GLint blue)
{
    this->_selectedColour = glm::vec3((GLfloat)red / 256.0f,
                                      (GLfloat)green / 256.0f,
                                      (GLfloat)blue / 256.0f);
}

glm::vec3 Model::getColour()
{
    return this->_colour;
}

glm::vec3 Model::getSelectedColour()
{
    return this->_selectedColour;
}

void Model::setMesh(Mesh *mesh)
{
    this->_mesh = mesh;
}

Mesh *Model::getMesh()
{
    return this->_mesh;
}

void Model::setSelectedMesh(Mesh *mesh)
{
    this->_selectedMesh = mesh;
}

Mesh *Model::getSelectedMesh()
{
    return this->_selectedMesh;
}

void Model::setGeometry(Geometry *geometry)
{
    this->_geometry = geometry;
}

Geometry *Model::getGeometry()
{
    return this->_geometry;
}

void Model::setSelectedMeshGeometry(Geometry *geometry)
{
    this->_selectedMeshGeometry = geometry;
}

Geometry *Model::getSelectedMeshGeometry()
{
    return this->_selectedMeshGeometry;
}

void Model::buildSelectedMeshGeometry()
{
    for (size_t i = 0; i < this->_geometry->getNumVertices(); i++)
    {
        Vertice vertice = this->_geometry->vertices[i];
        Vertice normal = this->_geometry->normals[i];

        this->_selectedMeshGeometry->addVertice(vertice.coords.x,
                                                vertice.coords.y,
                                                vertice.coords.z);

        this->_selectedMeshGeometry->addNormal(normal.coords.x,
                                               normal.coords.y,
                                               normal.coords.z);
    }
}

void Model::updateGeometriesByModelMatrix()
{
    this->_geometry->updateGeometryByModelMatrix(this->_modelMatrix);
    this->_selectedMeshGeometry->updateGeometryByModelMatrix(this->_modelMatrix);
}

void Model::selectFace(GLint index)
{
    // Retrieves face that is gonna be selected
    Face face = this->_geometry->faces[index];

    // Remove the face from the main geometry
    this->_geometry->removeFace(index);

    // Update the main geometry by the inverse of the model matrix, so it can keep the original coordinates
    glm::mat4 invModelMatrix = glm::inverse(this->_modelMatrix);
    this->_geometry->updateGeometryByModelMatrix(invModelMatrix);

    // Updates the main mesh to the new geometry
    Loader loader = Loader();
    this->_mesh = loader.geometryToMesh(this->_geometry);

    // Updates the geometry with the original model matrix
    this->_geometry->updateGeometryByModelMatrix(this->_modelMatrix);

    // Adds new face to the geometry of the selected mesh
    this->_selectedMeshGeometry->addFace(face.ind0, face.ind1, face.ind2);

    // Update the selected geometry by the inverse of the model matrix, so it can keep the original coordinates
    this->_selectedMeshGeometry->updateGeometryByModelMatrix(invModelMatrix);

    // Updates the selected mesh to the new geometry
    this->_selectedMesh = loader.geometryToMesh(this->_selectedMeshGeometry);

    // Updates the selected geometry with the original model matrix
    this->_selectedMeshGeometry->updateGeometryByModelMatrix(this->_modelMatrix);
}

void Model::setName(const char *name)
{
    this->_name = name;
}

const char *Model::getName()
{
    return this->_name;
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

void Model::renderSelectedMesh()
{
    this->_selectedMesh->render();
}

Model::~Model()
{
    free(this->_shader);
    free(this->_mesh);
    free(this->_selectedMesh);
    free(this->_geometry);
    free(this->_selectedMeshGeometry);
    free(this->_texture);
    free(this->_material);
}