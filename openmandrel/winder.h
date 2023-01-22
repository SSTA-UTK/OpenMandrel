#pragma once

#include "math.h"

struct WindStep {
    double windAngle;
    Vec3 windPosition; // phi, radius, axial height
    // Cartesian vectors, where z is axial height
    Vec3 bundleDirection;
    Vec3 bundleBidirection;
};
