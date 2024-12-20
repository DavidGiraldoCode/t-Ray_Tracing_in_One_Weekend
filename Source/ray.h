#pragma once

#include "vec3.h"
/// @brief A ray that get dispatched from the camera through a pixel on the viewport and on the scene
class ray
{
public:
    ray(){} // Default constructor
    
    /// @brief Creates a ray at a given origin, looking at a given direction
    /// @param ray_origen 
    /// @param ray_direction 
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