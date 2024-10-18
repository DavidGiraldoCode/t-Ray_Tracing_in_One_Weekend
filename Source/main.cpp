// g++ -std=c++20 *.cpp -o myRayTracer && ./myRayTracer
#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

color renderSky(double y)
{
    auto a = 0.5 * (y + 1.0);

    color startColor = color(1.0, 1.0, 1.0);
    color endColor = color(0.5, 0.7, 1.0);

    color interpolatedColor = ((1.0 - a) * startColor) + (a * endColor);
    return interpolatedColor;
}

color rayColor(const ray &r, const hittable_list &world)
{
    hit_record hitRecord;
    if (world.hit(r, 0, infinity, hitRecord))
    {
        return 0.5 * (hitRecord.normal + color(1, 1, 1));
    }

    return renderSky(unit_vector(r.direction()).y());
}

int main(int argc, char *argv[])
{
    // int imageWidth = 400;
    // int imageHeight = 400;
    // Sphere sphereA = Sphere(point3(-1,0,-1), 0.4);
    // Sphere sphereB = Sphere(point3(1,0,-1), 0.6);

    auto aspectRatio = 16.0 / 9.0; // Always remmember the floating part

    // ========================== Rendered image
    unsigned imageWidth = 800;
    unsigned imageHeight = unsigned(imageWidth / aspectRatio);
    imageHeight = imageHeight < 1 ? 1 : imageHeight; // Make sure is at least 1

    // ========================== Objects in world

    hittable_list world;

    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // ========================== Camera
    auto focalLenth = 1.0;
    auto camera = point3(0, 0, 0); // Eye
    // View port is the virtual square IN 3D SPACE (meaning is actually in the scene) containing the pixel grid that represent the image
    auto viewPortHeight = 2;
    auto viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);

    auto viewportU = vec3(viewPortWidth, 0, 0);
    auto viewportV = vec3(0, -viewPortHeight, 0);

    // Delta of pixel to pixel
    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    // Upper left pixel, check the solution using descritive geomtry
    auto viewportUpperLeft = camera - vec3(0, 0, focalLenth) - viewportU * 0.5 - viewportV * 0.5;
    auto pixel00 = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));

    // Defines the first line
    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    // Goes from Top to Bottom, and Left to Right
    for (size_t j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (size_t i = 0; i < imageWidth; i++)
        {
            // Normalized values [0,1]
            // auto r = double(i) / (imageWidth - 1);
            // auto g = double(j) / (imageHeight - 1);
            // auto b = 0;

            // color pixel = color(double(i) / (imageWidth - 1),
            //                     double(j) / (imageHeight - 1),
            //                     0);

            // Values from [0, 255]
            // int ir = int(r * 255);
            // int ig = int(g * 255);
            // int ib = int(b * 255);

            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';

            auto pixelCenter = pixel00 + (pixelDeltaU * i) + (pixelDeltaV * j);
            auto rayDirection = pixelCenter - camera;
            ray r(camera, rayDirection);

            color pixelColor = rayColor(r, world);
            // std::cout << pixelColor << " pixelColor\n";
            writeColor(std::cout, pixelColor);
        }
    }
    // return 0;
    std::clog << "\rDone.                 \n";
}