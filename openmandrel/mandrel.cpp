#include "mandrel.h"

AxisymmetricMandrelSegment::AxisymmetricMandrelSegment() { }

Vec2 AxisymmetricMandrelSegment::CylindricalCoords(double t) {
    return glm::vec2(Radius(t).real(), Height(t).real());
}

Vec2 AxisymmetricMandrelSegment::CylindricalDerivatives(double t) {
    double h = 1.0E-10;
    return glm::vec2(Radius(std::complex<double>(t, h)).imag()/h, Height(std::complex<double>(t, h)).imag()/h);
}

LinearTransitionMandrel::LinearTransitionMandrel(double D0, double D1, double L) :
    D0(D0),
    D1(D1),
    L(L) { }

std::complex<double> LinearTransitionMandrel::Radius(const std::complex<double>& t) {
    return 0.5*(D0*(1.0-t) + D1*t);
}

std::complex<double> LinearTransitionMandrel::Height(const std::complex<double>& t) {
    return t*L;
}

PowerSeriesMandrel::PowerSeriesMandrel(double power, double D0, double D1, double L) :
    power(power), D1(D1), L(L) {
    // D0=D1*pow(t0/(1.0+t0), power) => t0=pow(D0/D1, 1.0/power)/(1.0-pow(D0/D1, 1.0/power))
    t0 = pow(D0/D1, 1.0/power) / (1.0-pow(D0/D1, 1.0/power));
}

std::complex<double> PowerSeriesMandrel::Radius(const std::complex<double>& t) {
    return 0.5*D1*pow((t+t0)/(1.0+t0), power);
}

std::complex<double> PowerSeriesMandrel::Height(const std::complex<double>& t) {
    return t*L;
}

EllipticalMandrel::EllipticalMandrel(double D0, double D1, double L) :
    D1(D1), L(L) {
    // D0=D1*sqrt(1.0-pow(t0/(1.0+t0), 2.0)) => t0=sqrt(1.0-pow(D0/D1, 2.0))/(1.0 - sqrt(1.0-pow(D0/D1, 2.0)))
    t0 = sqrt(1.0-pow(D0/D1,2.0)) / (1.0 - sqrt(1.0-pow(D0/D1,2.0)));
}

std::complex<double> EllipticalMandrel::Radius(const std::complex<double>& t) {
    return 0.5*D1*sqrt(1.0-pow((t+t0)/(1.0+t0), 2.0));
}

std::complex<double> EllipticalMandrel::Height(const std::complex<double>& t) {
    return t*L;
}
