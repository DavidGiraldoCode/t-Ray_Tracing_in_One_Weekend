// g++ -std=c++20 *.cpp -o myRayTracer && ./myRayTracer

#include <iostream>

int main(int argc, char *argv[])
{
    int imageWidth = 400;
    int imageHeight = 400;

    // Defines the first line
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    // Goes from Top to Bottom, and Left to Right
    for (size_t j = 0; j < imageWidth; j++)
    {
        for (size_t i = 0; i < imageHeight; i++)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }
    return 0;
}