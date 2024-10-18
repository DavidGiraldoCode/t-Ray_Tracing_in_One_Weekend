#pragma once
#include "vec3.h"

using color = vec3;
/// @brief Write a color into the ppm file
/// @param output
/// @param pixelColor The values of the color are in normalize space [0,1], the method transforms then into byte range [0,255]

void writeColor(std::ostream &output, const color &pixelColor)
{
    //std::cout << pixelColor << " pixelColor inside writeColor\n";
    unsigned rByte = unsigned(pixelColor.x() * 255.999); // watchout (int) is NOT as int()
    unsigned gByte = unsigned(pixelColor.y() * 255.999);
    unsigned bByte = unsigned(pixelColor.z() * 255.999);

    output << rByte << ' ' << gByte << ' ' << bByte << '\n';
};
