// g++ -std=c++20 *.cpp -o myRayTracer && ./myRayTracer
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main(int argc, char *argv[])
{
    // ========================== Objects in world

    hittable_list world;

    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // ========================== Camera
    Camera cam = Camera();
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;

    //cam.render(world);
    std::cout << random_double(0.0, 5.0) << " random\n";

    return 0;
}