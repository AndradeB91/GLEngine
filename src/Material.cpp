#include "Material.h"

Material::Material()
{
    this->_specularIntensity = 0.0f;
    this->_shininess = 0.0f;
}

Material::Material(GLfloat specularIntensity, GLfloat shininess)
{
    this->_specularIntensity = specularIntensity;
    this->_shininess = shininess;
}

GLfloat Material::getSpecularIntensity()
{
    return this->_specularIntensity;
}

GLfloat Material::getShininess()
{
    return this->_shininess;
}

Material::~Material()
{
}
