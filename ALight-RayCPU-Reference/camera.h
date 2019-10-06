#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "quaternion.h"
#include "transform.h"

using namespace math;

class Camera
{
public:
    Camera(Transform transform = Transform(), float speed = 2, float sensitivity = 100) : m_transform(transform), m_speed(speed), m_sensitivity(sensitivity) { }

    void move(const vec3 &direction, float dt)
    {
        m_transform.setPosition(m_transform.getPosition() - direction * m_speed * dt);
    }

    void rotate(const vec3 &axis, float dt)
    {
        auto q = quaternion().euler(axis.x, axis.y, axis.z, m_sensitivity * dt);
        m_transform.setRotation((q * m_transform.getRotation()).normalize());
    }

    void setTransform(Transform t)
    {
        m_transform = t;
    }

    void setPosition(vec3 position)
    {
        m_transform.setPosition(position);
    }

    void setRotation(quaternion rotation)
    {
        m_transform.setRotation(rotation);
    }

    void setScale(vec3 scale)
    {
        m_transform.setScale(scale);
    }

    Transform getTransform() const
    {
        return m_transform;
    }

private:
    Transform m_transform;
    float m_speed;
    float m_sensitivity;
};

#endif
