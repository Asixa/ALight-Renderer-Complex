#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "math.h"

class Plane
{
public:
    Plane(vec3 position = vec3(), vec3 normal = vec3(0, 1, 0), Material material = Material()) : m_position(position), m_normal(normal), m_material(material) { }

    Intersection intersect(const Ray &r) const
    {
        vec3 P;
        float d, t;

        P = m_position - r.GetOrigin();
        d = vec3::dot(m_normal, r.GetDirection());

        if (d > 0.0f)
            return invalidIntersection;

        t = vec3::dot(P, m_normal) / d;

        if (t < EPSILON)
            return invalidIntersection;

        auto x = Intersection();
        x.setPosition(r.GetOrigin() + r.GetDirection() * t);
        x.setNormal(m_normal.normalize());
        x.setT(t);
        x.setMaterial(m_material);

        return x;
    }
private:
    vec3 m_position;
    vec3 m_normal;
    Material m_material;
protected:
};

#endif
