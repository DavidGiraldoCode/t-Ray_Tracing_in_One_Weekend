#pragma once
#include "interval.h"
#include "vec3.h"

using color = vec3;
/// @brief Write a color into the ppm file
/// @param output
/// @param pixelColor The values of the color are in normalize space [0,1], the method transforms then into byte range [0,255]
void writeColor(std::ostream &output, const color &pixelColor)
{
    //std::cout << pixelColor << " pixelColor inside writeColor\n";

    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    static const interval intensity(0.0, 0.999);

    unsigned rByte = unsigned( 256 * intensity.clamp(r));
    unsigned gByte = unsigned( 256 * intensity.clamp(g));
    unsigned bByte = unsigned( 256 * intensity.clamp(b));

    // unsigned rByte = unsigned(pixelColor.x() * 255.999); // watchout (int) is NOT as int()
    // unsigned gByte = unsigned(pixelColor.y() * 255.999);
    // unsigned bByte = unsigned(pixelColor.z() * 255.999);

    output << rByte << ' ' << gByte << ' ' << bByte << '\n';
};
