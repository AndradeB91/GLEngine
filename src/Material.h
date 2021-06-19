#include "GL/glew.h"

class Material
{

public:
    Material();

    Material(GLfloat specularIntensity, GLfloat shininess);

    GLfloat getSpecularIntensity();
    GLfloat getShininess();

    ~Material();

private:
    GLfloat _specularIntensity;
    GLfloat _shininess;
};