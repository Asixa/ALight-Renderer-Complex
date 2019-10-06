#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

using namespace math;

enum Refl_t
{
    DIFF, SPEC, REFR, GLOS
};

/*  Material
    refl_t = Surface type
    emittance = Surface emission color
    reflectance = Surface reflection color
    ior = Index of refraction, glass = ~1.52f
    roughness = cook-torrance brdf term
    fresnel = cook-torrance brdf term
    density = cook-torrance brdf term
*/
class Material
{
public:
    Material(Refl_t refl_t = DIFF, vec3 em = vec3(), vec3 re = vec3(), float ior = 1.52f, float roughness = 0.25f, float fresnel = 1.0f, float density = 0.33f):
        m_refl_t(refl_t), m_emittance(em), m_reflectance(re), m_ior(ior), m_roughness(roughness), m_fresnel(fresnel), m_density(density) { }

    Refl_t getReflT() const
    {
        return m_refl_t;
    }

    vec3 getEmittance() const
    {
        return m_emittance;
    }

    vec3 getReflectance() const
    {
        return m_reflectance;
    }

    float getIOR() const
    {
        return m_ior;
    }

    float getRoughness() const
    {
        return m_roughness;
    }

    float getFresnel() const
    {
        return m_fresnel;
    }

    float getDensity() const
    {
        return m_density;
    }

private:
    Refl_t m_refl_t;
    vec3 m_emittance;
    vec3 m_reflectance;
    float m_ior;
    float m_roughness;
    float m_fresnel;
    float m_density;
};

#endif
