#pragma once
#include "ray.h"

// Data structure to store the hit
class hit_record
{
public:
    point3 point;
    double t;
    vec3 normal;
};

// Interface to define the behavior
class Ihittable
{
public:
    virtual ~Ihittable() = default;

    virtual bool hit( const ray& r, double rT_Min,  double rT_Max, hit_record &hitRecord) const = 0;
};