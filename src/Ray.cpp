#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
    this->_origin = origin;
    this->_direction = direction;
}

void Ray::setOrigin(glm::vec3 origin)
{
    this->_origin = origin;
}

void Ray::setDirection(glm::vec3 direction)
{
    this->_direction = direction;
}

glm::vec3 Ray::getOrigin()
{
    return this->_origin;
}

glm::vec3 Ray::getDirection()
{
    return this->_direction;
}

/*
 * Moller-Trumbore intersection.
 * https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
 */
int Ray::intersectsFace(glm::vec3 va, glm::vec3 vb, glm::vec3 vc,
                        float *t)
{
    const float EPSILON = 0.000001;

    glm::vec3 edge1, edge2, pvec, qvec, tvec;
    edge1 = vb - va;
    edge2 = vc - va;

    pvec = glm::cross(this->_direction, edge2);

    float det = glm::dot(edge1, pvec);

    if (det < EPSILON)
        return false;

    if (det > -EPSILON && det < EPSILON)
        return 0;
    float invdet = 1.0f / det;

    tvec = this->_origin - va;
    float u = glm::dot(tvec, pvec) * invdet;

    if (u < 0.0f || u > 1.0f)
        return 0;

    qvec = glm::cross(tvec, edge1);
    float v = glm::dot(this->_direction, qvec) * invdet;
    if (v < 0.0f || u + v > 1.0f)
        return 0;

    *t = glm::dot(edge2, qvec) * invdet;
    if (*t <= EPSILON)
        return 0;

    return 1;
}

int Ray::intersectsGeometry(Geometry geometry)
{
    GLboolean intersect = false;
    GLfloat minT = FLT_MAX;

    for (int i = 0; i < geometry.getNumFaces(); i++)
    {
        Face face = geometry.faces[i];
        Vertice v0 = geometry.vertices[face.ind0];
        Vertice v1 = geometry.vertices[face.ind1];
        Vertice v2 = geometry.vertices[face.ind2];

        GLfloat newt;
        if (this->intersectsFace(v0.coords, v1.coords, v2.coords, &newt))
        {
            if (newt < minT)
            {
                minT = newt;
                intersect = true;
            }
        }
    }

    return intersect;
}

int Ray::intersectsGeometry(Geometry geometry, int *indice)
{
    GLboolean intersect = false;
    GLfloat minT = FLT_MAX;

    for (int i = 0; i < geometry.getNumFaces(); i++)
    {
        Face face = geometry.faces[i];
        Vertice v0 = geometry.vertices[face.ind0];
        Vertice v1 = geometry.vertices[face.ind1];
        Vertice v2 = geometry.vertices[face.ind2];

        GLfloat newt;
        if (this->intersectsFace(v0.coords, v1.coords, v2.coords, &newt))
        {
            if (newt < minT)
            {
                minT = newt;
                intersect = true;
                *indice = i;
            }
        }
    }

    return intersect;
}

Ray::~Ray()
{
}
