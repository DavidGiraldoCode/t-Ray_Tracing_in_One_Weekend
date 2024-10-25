#pragma once
#include "hittable.h"
// #include "vec3.h"

/// @brief Represents an implicit definition of a Sphere, and implements Ihitable
class Sphere : public Ihittable
{
public:
    Sphere(const point3 &center, double radius) : m_center(center), m_radius(radius) {}

    // bool hit(const ray &r, double rT_Min, double rT_Max, hit_record &hitRecord) const

    /// @brief Computes the ray-sphere intersection test based on a interval we define.
    /// @param r The current ray
    /// @param rayT The interval of T that we are intrested in.
    /// @param hitRecord Is the external reference of the other hits that current ray was encounter
    /// @return Returns whethers the ray is intersecting the sphere or not.
    bool hit(const ray &r, interval rayT, hit_record &hitRecord) const
    {
        vec3 QC = m_center - r.origin();

        double a = r.direction().length_squared();
        double h = dot(r.direction(), QC);
        double c = QC.length_squared() - (m_radius * m_radius);

        double discriminat = (h * h) - (a * c);

        if (discriminat < 0) // The ray missed the sphere
            return false;

        // The ray intersected the shphere, so we finish computing the cuadratic function
        // First with (-)
        double sqrt = std::sqrt(discriminat); // store the sqrt to avoid repeating this computation
        double root = (h - sqrt) / a;

        // We check if the t is within the interval
        // if (root <= rT_Min || rT_Max <= root) // if (-) is outside the range, try with (+)
        if (!rayT.surrounds(root))
        {
            // Then with (+)
            root = (h + sqrt) / a;
            // if (root <= rT_Min || rT_Max <= root)
            if (!rayT.surrounds(root))
                return false;
        }

        // If pases the test, we store the hit record because it means it is with the interval
        hitRecord.t = root;
        hitRecord.point = r.at(hitRecord.t);
        // hitRecord.normal = (hitRecord.point - m_center) / m_radius;
        // Normal always against the Ray
        vec3 outward_normal = unit_vector((hitRecord.point - m_center) / m_radius);
        hitRecord.setFaceNormal(r, outward_normal); // Compute the direction of the normal

        return true;
    }

private:
    point3 m_center;
    double m_radius;
};