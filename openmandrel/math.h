#pragma once

#include <utility>

#define PI 4.0*atan(1.0)

class Vec2 {
public:
    double x, y;

    Vec2(double x, double y) :
        x(x),
        y(y) { }
};

class Vec3 {
public:
    double x, y, z;

    Vec3(double x, double y, double z) :
        x(x), y(y), z(z) { }
};

class Quadrature {
public:
    enum class Type {
        GUASS,
        TRAPEZOID,
        COUNT
    } type;
    const int size;
    // sample points (bounded in [lowerRange, upperRange]) and sample weights
    const std::pair<double, double>* xw;

    Quadrature(int size, double lowerRange, double upperRange, Type type);
    ~Quadrature();
    Quadrature(Quadrature&) = delete;
    Quadrature& operator=(const Quadrature&) = delete;
};
