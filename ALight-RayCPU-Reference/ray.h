#ifndef RAY_H
#define RAY_H

#include "vec3.h"

using namespace math;

class Ray
{
public:
    Ray(vec3 origin = vec3(), vec3 direction = vec3()) : m_origin(origin), m_direction(direction.normalize()) { }

    void SetOrigin(const vec3 &v)
    {
        m_origin = v;
    }

    void SetDirection(const vec3 &v)
    {
        m_direction = v.normalize();
    }

    vec3 GetOrigin() const
    {
        return m_origin;
    }

    vec3 GetDirection() const
    {
        return m_direction;
    }
private:
    vec3 m_origin;
    vec3 m_direction;
};

#endif
