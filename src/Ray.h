#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
    Ray();

    Ray(glm::vec3 origin, glm::vec3 direction);

    void setOrigin(glm::vec3 origin);
    void setDirection(glm::vec3 direction);

    glm::vec3 getOrigin();
    glm::vec3 getDirection();

    int faceIntersection(glm::vec3 va, glm::vec3 vb, glm::vec3 vc,
                         float *t);

    ~Ray();

private:
    glm::vec3 _origin, _direction;
};
