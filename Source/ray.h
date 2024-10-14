#pragma once

#include "vec3.h"

class ray
{
public:
    ray(){} // Default constructor
    ray(const point3 & ray_origen, const vec3 & ray_direction): m_origin(ray_origen), m_direction(ray_direction){}

    const point3& origin() const { return m_origin; }
    const vec3& direction() const { return m_direction; }

    point3 at(double t) const
    {
        return m_origin + (m_direction * t);
    }

private:
    point3 m_origin;
    vec3 m_direction;
};