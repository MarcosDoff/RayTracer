#pragma once
#include "vec3.h"

using Color = Vec3;

void writeColor(std::ostream& out, const Color& pixelColor, int samplesPerPixel);