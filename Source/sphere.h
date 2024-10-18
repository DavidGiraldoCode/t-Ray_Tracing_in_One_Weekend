#pragma once
#include "hittable.h"
//#include "vec3.h"

class Sphere : public Ihittable
{
public:
    Sphere(const point3 &center, double radius) : m_center(center), m_radius(radius) {}

    bool hit(const ray &r, double rT_Min, double rT_Max, hit_record &hitRecord) const
    {
        vec3 QC = m_center - r.origin();

        double a = r.direction().length_squared();
        double h = dot(r.direction(), QC);
        double c = QC.length_squared() - (m_radius * m_radius);

        double discriminat = (h * h) - (a * c);

        if (discriminat < 0)
            return false;

        double sqrt = std::sqrt(discriminat); // store the sqrt to avoid repeating this computation
        double root = (h - sqrt) / a;

        if (root <= rT_Min || rT_Max <= root) // if (-) is outside the range, try with (+)
        {
            root = (h + sqrt) / a;
            if (root <= rT_Min || rT_Max <= root)
                return false;
        }

        // It pases the test, so store the hit record
        hitRecord.t = root;
        hitRecord.point = r.at(hitRecord.t);
        //hitRecord.normal = (hitRecord.point - m_center) / m_radius;
        vec3 outward_normal = unit_vector((hitRecord.point - m_center) / m_radius);
        hitRecord.setFaceNormal(r, outward_normal); //Compute the direction of the normal

        return true;
    }

private:
    point3 m_center;
    double m_radius;
};