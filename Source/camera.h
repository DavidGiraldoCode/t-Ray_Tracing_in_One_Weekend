#pragma once
#include "hittable.h"

class Camera
{
public:
    /// @brief Defines the proportions of the final image, remmeber the #.0 point at the end
    double aspectRatio = 16.0 / 9.0;

    /// @brief Define the final size in pixels of the final image, it must be a positive integer
    unsigned imageWidth = 1;

    /// @brief The number of rays to shoot to compute the color of the image
    unsigned samplesPerPixel = 10;

    /// @brief This is a default construct, the ower class of the instance must set `aspectRatio` and `imageWidth` using "." notation
    Camera() = default;

    /// @brief Renders the final image by traversing the view port's pixel grid and checking for
    /// a hit for each of the objects in the scene.
    /// @note Complexity O(n*m) `n` numer of pixels `m` number of objects
    /// @param world The list of all the objects in the scene
    void render(const hittable_list &world)
    {
        initialize();
        // Defines the first line
        std::cout << "P3\n"
                  << imageWidth << ' ' << imageHeight << "\n255\n";

        // Goes from Top to Bottom, and Left to Right
        for (size_t j = 0; j < imageHeight; j++)
        {
            std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
            for (size_t i = 0; i < imageWidth; i++)
            {
                color pixelColor(0, 0, 0); // The cumulated start in cero, is back, we have not get any light
                for (size_t sample = 0; sample < samplesPerPixel; sample++)
                {
                    ray r = getRay(i, j);
                    pixelColor += rayColor(r, world);
                }
                // Compute the average of the color that all the ray samples gathered
                // pixelColor *= sampleScaleFactor;

                // auto pixelCenter = pixel00 + (pixelDeltaU * i) + (pixelDeltaV * j);
                // auto rayDirection = pixelCenter - cameraCenter;
                // ray r(cameraCenter, rayDirection);
                // color pixelColor = rayColor(r, world);

                writeColor(std::cout, pixelColor * sampleScaleFactor);
            }
        }
        // return 0;
        std::clog << "\rDone.                 \n";
    }

private:
    unsigned imageHeight = 0;
    double sampleScaleFactor;
    point3 cameraCenter;
    vec3 pixelDeltaU; // The vector representing horizontal distance between pixels' center
    vec3 pixelDeltaV; // The vector representing vertical distance between pixels' center
    point3 pixel00;   // The location of the first pixel at the origen of the view port `[0,0]` in the upper left corner

    /// @brief Initilialize the view port ratio and the rendered image size,
    /// as well as the pixel origin at the top left corner of the screen.
    void initialize()
    {
        // ========================== Rendered image
        imageHeight = unsigned(imageWidth / aspectRatio);
        imageHeight = imageHeight < 1 ? 1 : imageHeight; // Make sure is at least 1

        sampleScaleFactor = 1.0 / samplesPerPixel; // We store this value as an scalar becase division is more computational costly

        // ========================== Camera settings
        auto focalLenth = 1.0;
        cameraCenter = point3(0, 0, 0); // Eye position

        // ========================== View port
        // View port is the virtual square IN 3D SPACE (meaning is actually in the scene) containing the pixel grid that represent the image
        auto viewPortHeight = 2;
        auto viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);

        // Vector that describes the horizontal size of the view port
        auto viewportU = vec3(viewPortWidth, 0, 0);
        // Vector that describes the vertizal size of the view port. Recall that Y goes from top to bottom
        auto viewportV = vec3(0, -viewPortHeight, 0);

        // Delta of a pixel center to another pixel center
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        // Upper left pixel, check the solution using descritive geometry
        auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLenth) - viewportU * 0.5 - viewportV * 0.5;
        // Offset the origin pixel by half of the addition between the horizontal and vertical delta.
        pixel00 = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));
    }

    const ray getRay(int i, int j) const
    {

        // auto pixelCenter = pixel00 + (pixelDeltaU * i) + (pixelDeltaV * j);
        vec3 offSet = sampleSquare();

        // In the same way we computed the posiiton of each single pixel sample at the center,
        // We use the offset generated in the unit squate to offset the deltaV and deltaU
        auto randomPixelSamplePosition = pixel00 + (pixelDeltaU * (i + offSet.x())) + (pixelDeltaV * (j + offSet.y()));

        point3 rayOrigin = cameraCenter;
        vec3 direction = randomPixelSamplePosition - rayOrigin;

        return ray(rayOrigin, direction);
    }

    /// @brief Create a random position inside the unit square centered at the origin. This position is going
    /// offset the position of the sample ray in the pixel
    /// @return Returns the point
    vec3 sampleSquare() const
    {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    /// @brief Interpolates between two colors to render a sky gradient base on the Y component of the Ray direction
    /// @param y the Y unit component of the Ray direction
    /// @return The final interpolated color of the sky
    color renderSky(double y) const
    {
        auto a = 0.5 * (y + 1.0);

        color startColor = color(1.0, 1.0, 1.0);
        color endColor = color(0.5, 0.7, 1.0);

        color interpolatedColor = ((1.0 - a) * startColor) + (a * endColor);
        return interpolatedColor;
    }

    /// @brief Computes the ray color that passes through a pixel
    /// @param r Reference to the ray
    /// @param world Reference to the world
    /// @return The final color of that pixel
    color rayColor(const ray &r, const hittable_list &world)
    {
        hit_record hitRecord;
        // The interval goes from cero to positive infinity
        if (world.hit(r, interval(0, infinity), hitRecord))
        {
            return 0.5 * (hitRecord.normal + color(1, 1, 1));
        }

        return renderSky(unit_vector(r.direction()).y());
    }
};