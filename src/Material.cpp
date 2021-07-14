#include "Material.h"

Material::Material()
{
    this->_specularIntensity = 0.0f;
    this->_shininess = 0;
}

Material::Material(GLfloat specularIntensity, GLint shininessFactor)
{
    this->_specularIntensity = specularIntensity;
    this->_shininess = shininessFactor;
}

GLfloat Material::getSpecularIntensity()
{
    return this->_specularIntensity;
}

GLint Material::getShininess()
{
    return pow(2, this->_shininess);
}

GLint Material::getShininessFactor()
{
    return this->_shininess;
}

Material::~Material()
{
}
