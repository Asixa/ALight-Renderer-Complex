#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "quaternion.h"
#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "math.h"

class Triangle
{
public:
    Triangle(vec3 v0 = vec3(), vec3 v1 = vec3(), vec3 v2 = vec3(), Material material = Material()) : m_material(material)
    {
        m_vertices[0] = v0;
        m_vertices[1] = v1;
        m_vertices[2] = v2;
        calcNormal();
        iNormals = false;
    }

    Triangle(vec3 v0 = vec3(), vec3 v1 = vec3(), vec3 v2 = vec3(), vec3 n0 = vec3(), vec3 n1 = vec3(), vec3 n2 = vec3(), Material material = Material()) : m_material(material)
    {
        m_vertices[0] = v0;
        m_vertices[1] = v1;
        m_vertices[2] = v2;
        m_normals[0] = n0;
        m_normals[1] = n1;
        m_normals[2] = n2;
        iNormals = true;
    }

    Intersection intersect(const Ray &r) const
    {
        vec3 P, Q, T;
        float d, inv_d, u, v, t;

        vec3 edge_a = m_vertices[1] - m_vertices[0];
        vec3 edge_b = m_vertices[2] - m_vertices[0];

        P = vec3::cross(r.GetDirection(), edge_b);
        d = vec3::dot(edge_a, P);

        if (d < EPSILON)
            return invalidIntersection;

        inv_d = 1.0f / d;
        T = r.GetOrigin() - m_vertices[0];
        u = vec3::dot(T, P) * inv_d;

        if (u < 0.0f || u > 1.0f)
            return invalidIntersection;

        Q = vec3::cross(T, edge_a);
        v = vec3::dot(r.GetDirection(), Q) * inv_d;

        if (v < 0.0f || u + v > 1.0f)
            return invalidIntersection;

        t = vec3::dot(edge_b, Q) * inv_d;

        if (t < EPSILON)
            return invalidIntersection;

        auto x = Intersection();
        x.setPosition(r.GetOrigin() + r.GetDirection() * t);
        x.setNormal(m_normals[0]);
        x.setT(t);
        x.setMaterial(m_material);

        return x;
    }

    void calcNormal()
    {
        m_normals[0] = vec3::cross(m_vertices[1] - m_vertices[0], m_vertices[2] - m_vertices[0]).normalize();
    }

    void translate(vec3 v)
    {
        m_vertices[0] += v;
        m_vertices[1] += v;
        m_vertices[2] += v;
    }

    void rotate(quaternion q)
    {
        m_vertices[0] = m_vertices[0] * q;
        m_vertices[1] = m_vertices[1] * q;
        m_vertices[2] = m_vertices[2] * q;
    }

    void scale(vec3 v)
    {
        m_vertices[0] *= v;
        m_vertices[1] *= v;
        m_vertices[2] *= v;
    }

    std::string toString() const
    {
        return "Triangle[\n" + m_vertices[0].toString() + "\n" + m_vertices[1].toString() + "\n" + m_vertices[2].toString();
    }

    Material getMaterial() const
    {
        return m_material;
    }
private:
    vec3 m_vertices[3];
    vec3 m_normals[3];
    Material m_material;
    bool iNormals;
protected:
};

#endif // TRIANGLE_H
