#include "color.h"
#include <iostream>
#include "hittable.h"

inline double linearToGamma(double linear_component)
{
    return sqrt(linear_component);
}

void writeColor(std::ostream& out, uint8_t r, uint8_t g, uint8_t b) {

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(r) << ' '
        << static_cast<int>(g) << ' '
        << static_cast<int>(b) << '\n';
}