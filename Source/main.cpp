// g++ -std=c++20 *.cpp -o myRayTracer && ./myRayTracer

#include <iostream>
#include "vec3.h"
#include "color.h"

int main(int argc, char *argv[])
{
    int imageWidth = 400;
    int imageHeight = 400;

    // Defines the first line
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    // Goes from Top to Bottom, and Left to Right
    for (size_t j = 0; j < imageHeight; j++)
    {
        for (size_t i = 0; i < imageWidth; i++)
        {
            // Normalized values [0,1]
            // auto r = double(i) / (imageWidth - 1);
            // auto g = double(j) / (imageHeight - 1);
            // auto b = 0;

            color pixel = color(double(i) / (imageWidth - 1),
                                double(j) / (imageHeight - 1),
                                0);

            // Values from [0, 255]
            // int ir = int(r * 255);
            // int ig = int(g * 255);
            // int ib = int(b * 255);

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';

            writeColor(std::cout , pixel);
        }
    }
    //return 0;
    std::clog << "\rDone.                 \n";
}