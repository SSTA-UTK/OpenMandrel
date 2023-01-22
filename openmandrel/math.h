#pragma once

#include <glm/glm.hpp>
#include <utility>

#define PI 4.0*atan(1.0)

typedef glm::vec<2, double> Vec2;
typedef glm::vec<3, double> Vec3;

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
