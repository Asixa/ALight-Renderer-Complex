#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec3.h"
#include "quaternion.h"

using namespace math;

class Transform
{
public:
    Transform(vec3 position = vec3(0, 0, 0), quaternion rotation = quaternion().identity(), vec3 scale = vec3(1, 1, 1)) : m_position(position), m_rotation(rotation), m_scale(scale) { }

    void setPosition(const vec3 v)
    {
        m_position = v;
    }

    void setRotation(const quaternion q)
    {
        m_rotation = q;
    }

    void setScale(const vec3 v)
    {
        m_scale = v;
    }

    vec3 getPosition() const
    {
        return m_position;
    }

    quaternion getRotation() const
    {
        return m_rotation;
    }

    vec3 getScale() const
    {
        return m_scale;
    }
private:
    vec3 m_position;
    quaternion m_rotation;
    vec3 m_scale;
};

#endif
