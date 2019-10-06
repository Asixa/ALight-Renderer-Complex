#ifndef QUATERNION_H
#define QUATERNION_H

#include <string>
#include <cmath>
#include "vec3.h"

namespace math
{

struct quaternion;
extern vec3 operator*(const vec3 &v, const quaternion &q);

struct quaternion
{
    float w, x, y, z;

    quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f) : w(w), x(x), y(y), z(z) { }

    std::string toString() const
    {
        return "quaternion[" + std::to_string(w) + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "]";
    }

    quaternion operator*(const quaternion &q) const
    {
        auto result = quaternion();

        result.w = w * q.w - x * q.x - y * q.y - z * q.z;
        result.x = w * q.x + x * q.w + y * q.z - z * q.y;
        result.y = w * q.y - x * q.z + y * q.w + z * q.x;
        result.z = w * q.z + x * q.y - y * q.x + z * q.w;

        return result;
    }

    quaternion operator*(const vec3 &v) const
    {
        auto result = quaternion();

        result.w = -x * v.x - y * v.y - z * v.z;
        result.x = w * v.x + y * v.z - z * v.y;
        result.y = w * v.y + z * v.x - x * v.z;
        result.z = w * v.z + x * v.y - y * v.x;

        return result;
    }

    float length() const
    {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    quaternion normalize() const
    {
        auto l = length();
        return quaternion(w / l, x / l, y / l, z / l);
    }

    quaternion conjugate() const
    {
        return quaternion(w, -x, -y, -z);
    }

    quaternion euler(float x, float y, float z, float theta)
    {
        theta = theta * PI / 180.0f;

        this->w = std::cos(theta / 2.0f);
        this->x = x * std::sin(theta / 2.0f);
        this->y = y * std::sin(theta / 2.0f);
        this->z = z * std::sin(theta / 2.0f);

        return *this;
    }

    quaternion identity()
    {
        w = 1.0f;
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;

        return *this;
    }

    vec3 getForwardVector() const
    {
        return vec3(0, 0, 1) **this;
    }

    vec3 getUpVector() const
    {
        return vec3(0, 1, 0) **this;
    }

    vec3 getRightVector() const
    {
        return vec3(1, 0, 0) **this;
    }
};

inline vec3 operator*(const vec3 &v, const quaternion &q)
{
    auto result = quaternion();
    result = q * v * q.conjugate();
    return vec3(result.x, result.y, result.z);
}

}

#endif
