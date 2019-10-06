#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vec3.h"
#include "material.h"

using namespace math;

class Intersection
{
public:
    Intersection(vec3 position = vec3(), vec3 normal = vec3(), float t = -1.0f, Material material = Material()) : m_position(position), m_normal(normal), m_t(t), m_material(material) { }

    void setPosition(const vec3 v)
    {
        m_position = v;
    }

    void setNormal(const vec3 v)
    {
        m_normal = v;
    }

    void setT(const float f)
    {
        m_t = f;
    }

    void setMaterial(const Material m)
    {
        m_material = m;
    }

    vec3 getPosition() const
    {
        return m_position;
    }

    vec3 getNormal() const
    {
        return m_normal;
    }

    float getT() const
    {
        return m_t;
    }

    Material getMaterial() const
    {
        return m_material;
    }

    inline bool operator==(const Intersection &x)
    {
        return m_position == x.m_position && m_normal == x.m_normal && m_t == x.m_t;
    }

    inline bool operator!=(const Intersection &x)
    {
        return !(*this == x);
    }
private:
    vec3 m_position;
    vec3 m_normal;
    float m_t;
    Material m_material;
protected:
};

static Intersection invalidIntersection = Intersection();

#endif
