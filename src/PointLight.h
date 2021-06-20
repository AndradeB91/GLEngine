#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();

    PointLight(GLfloat red,
               GLfloat green,
               GLfloat blue,
               GLfloat ambientIntensity,
               GLfloat diffuseIntensity,
               GLfloat xPos,
               GLfloat yPos,
               GLfloat zPos,
               GLfloat constant,
               GLfloat linear,
               GLfloat exponent);

    glm::vec3 getPosition();
    GLfloat getConstant();
    GLfloat getLinear();
    GLfloat getExponent();

    ~PointLight();

private:
    glm::vec3 _position;

    GLfloat _constant, _linear, _exponent;
};
