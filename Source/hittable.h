#pragma once
//#include "ray.h"

// Data structure to store the hit
class hit_record
{
public:
    point3 point;
    double t;
    vec3 normal;
    bool frontFace;

    void setFaceNormal(const ray & r, const vec3& outward_normal)
    {
        //we decide to have the normals always point against the ray
        /*
        vec3 rDir = unit_vector(r.direction());
        if(dot(rDir, outward_normal) > 0) // The ray is hitting form inside
        {
            frontFace = false;
            normal = -outward_normal; 
        }
        else
        {
            frontFace = true;
            normal = outward_normal;
        }*/// A more elegant approach

        frontFace = dot(r.direction(), outward_normal) < 0;
        normal = frontFace ? outward_normal : -outward_normal;

    }
};

// Interface to define the behavior
class Ihittable
{
public:
    virtual ~Ihittable() = default;

    virtual bool hit( const ray& r, double rT_Min,  double rT_Max, hit_record &hitRecord) const = 0;
};