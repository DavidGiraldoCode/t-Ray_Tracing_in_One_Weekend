// g++ -std=c++20 *.cpp -o myRayTracer && ./myRayTracer

#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

void setImageAndViewPort()
{
    auto aspectRatio = 9 / 16;

    unsigned imageWidth = 800;
    unsigned imageHeight = unsigned(imageWidth / aspectRatio);
    imageHeight = imageHeight < 1 ? 1 : imageHeight; // Make sure is at least 1

    // View port is the virtual square IN 3D SPACE (meaning is actully in the scene) containing the pixel grid that represent the image
    auto viewPortHeight = 2;
    auto viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);
}

color rayColor(const ray &r)
{
    vec3 unitDirection = unit_vector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);

    //std::cout << double(unitDirection.y()) << " unitDirection.y()\n";
    //std::cout << double(a) << " a\n";
    color startColor = color(1.0, 1.0, 1.0);
    color endColor = color(0.5, 0.7, 1.0);

    color interpolatedColor = ((1.0 - a) * startColor) + (a * endColor);
    //std::cout << interpolatedColor << " interpolatedColor\n";

    return interpolatedColor;//(1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));
}

int main(int argc, char *argv[])
{
    // int imageWidth = 400;
    // int imageHeight = 400;

    auto aspectRatio = 16.0 / 9.0; // Always remmember the floating part

    // Rendered image
    unsigned imageWidth = 400;
    unsigned imageHeight = unsigned(imageWidth / aspectRatio);
    imageHeight = imageHeight < 1 ? 1 : imageHeight; // Make sure is at least 1

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
    auto viewportUpperLeft = camera - vec3(0, 0, focalLenth) - viewportU - viewportV;
    auto pixel00 = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));

    // Defines the first line
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

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

            color pixelColor = rayColor(r);
            //std::cout << pixelColor << " pixelColor\n";
            writeColor(std::cout , pixelColor);
        }
    }
    // return 0;
    std::clog << "\rDone.                 \n";
}