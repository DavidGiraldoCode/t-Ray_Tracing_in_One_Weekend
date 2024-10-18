#pragma once
#include "hittable.h"

// #include <memory>
#include <vector>

// using std::make_shared;
// using std::shared_ptr;

class hittable_list : public Ihittable
{
public:
    hittable_list() = default;
    hittable_list(shared_ptr<Ihittable> object) { add(object); }; // We can create an instance by adding a first hittable object in the constructor

    /*
    Recall that shared pointers have transferable ownership, multiple objects can own this pointer
    */
    std::vector<shared_ptr<Ihittable>> objects; // Smart pointers

    void add(shared_ptr<Ihittable> object)
    {
        objects.push_back(object);
    }

    void clear()
    {
        objects.clear();
    }

    /// @brief Keeps track of the closest t value for each time the ray hits something, by traversing a vector of Ihittable objects
    /// @note O(n)
    /// @param r The ray beging shoot through the pixel
    /// @param rayT in the new interval that hold min and max
    /// @param rT_Min (old) Minimun t value
    /// @param rT_Max (old) Maximum t value, and closest so far
    /// @param hitRecord The record that is being updated based on the smallest rT_Max, at the end holds the normal to shade the pixel
    /// @return whether theres a hit or not
    bool hit(const ray &r, interval rayT, /*double rT_Min, double rT_Max*/ hit_record &hitRecord) const override
    {
        hit_record temporalRecord;
        bool hitSomething = false;
        auto closestSoFar = rayT.max; //rT_Max;

        for (const auto &object : objects)
        {
            if (object->hit(r, interval(rayT.min, closestSoFar), temporalRecord))
            {
                hitSomething = true;
                /*
                hitSomething is only set to true if an object is hit, and it stays true once a hit is detected.
                */
                closestSoFar = temporalRecord.t;
                hitRecord = temporalRecord;
            }
        }

        return hitSomething;
    }
};