#include "color.h"
#include <iostream>
#include "hittable.h"

inline double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}

void writeColor(std::ostream& out, const Color& pixelColor, int samplesPerPixel) {

    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    auto scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    const Interval intensity(0.0000, 0.9999);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}