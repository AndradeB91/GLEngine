#include "PointLight.h"

PointLight::PointLight() : Light()
{
    this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_constant = 1.0f;
    this->_linear = 0.0f;
    this->_exponent = 0.0f;
}

PointLight::PointLight(GLfloat red,
                       GLfloat green,
                       GLfloat blue,
                       GLfloat ambientIntensity,
                       GLfloat diffuseIntensity,
                       GLfloat xPos,
                       GLfloat yPos,
                       GLfloat zPos,
                       GLfloat constant,
                       GLfloat linear,
                       GLfloat exponent) : Light(red,
                                                 green,
                                                 blue,
                                                 ambientIntensity,
                                                 diffuseIntensity)
{
    this->_position = glm::vec3(xPos, yPos, zPos);
    this->_constant = constant;
    this->_linear = linear;
    this->_exponent = exponent;

    static const char *vertexShader = "shaders/light/shader.vert";
    static const char *fragmentShader = "shaders/light/shader.frag";

    GLfloat *vertices;
    unsigned int *indices;
    int numVertices;
    int numIndices;

    Primitive::generateSphere(20, 20, 0.1,
                              vertices, indices,
                              numVertices, numIndices);

    this->_model = new Model(vertexShader,
                             fragmentShader,
                             NULL,
                             vertices,
                             indices,
                             numVertices,
                             numIndices,
                             3);

    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, this->_position);
    this->_model->setModelMatrix(modelMatrix);
}

void PointLight::setPosition(glm::vec3 position)
{
    this->_position = position;
}

glm::vec3 PointLight::getPosition()
{
    return this->_position;
}

GLfloat PointLight::getConstant()
{
    return this->_constant;
}

GLfloat PointLight::getLinear()
{
    return this->_linear;
}

GLfloat PointLight::getExponent()
{
    return this->_exponent;
}

Model *PointLight::getModel()
{
    return this->_model;
}

PointLight::~PointLight()
{
}
