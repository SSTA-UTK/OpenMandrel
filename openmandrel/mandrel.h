#pragma once

#include "math.h"
#include <complex>
#include <vector>
#include <memory>

class AxisymmetricMandrelSegment {
public:
    AxisymmetricMandrelSegment();

    // Parametric functions, t is 0.0 to 1.0. Height must start at 0.0 and increase onwards
    virtual std::complex<double> Radius(const std::complex<double>& t) = 0;
    virtual std::complex<double> Height(const std::complex<double>& t) = 0;

    // Returns { radius, height }
    Vec2 CylindricalCoords(double t);
    // Returns { dradius/dt, dheight/dt }
    Vec2 CylindricalDerivatives(double t);
};

class AxisymmetricMandrel {
public:
    // Will only return true if geometry is continuous and fits within machine bounds
    bool IsValid();
    // Must be called before asking for which geometry is at which location
    void Prepare();
private:
    struct SegmentInfo {
        std::unique_ptr<AxisymmetricMandrelSegment> geometry;
        double cachedLength;
    };
    std::vector<SegmentInfo> segments;
};

class LinearTransitionMandrel : public AxisymmetricMandrelSegment {
private:
    double D0, D1, L;
public:
    LinearTransitionMandrel(double D0, double D1, double L);
    
    std::complex<double> Radius(const std::complex<double>& t) override;
    std::complex<double> Height(const std::complex<double>& t) override;
};

class PowerSeriesMandrel : public AxisymmetricMandrelSegment {
private:
    double power;
    double D1, L, t0;
public:
    PowerSeriesMandrel(double power, double D0, double D1, double L);

    std::complex<double> Radius(const std::complex<double>& t) override;
    std::complex<double> Height(const std::complex<double>& t) override;
};

class EllipticalMandrel : public AxisymmetricMandrelSegment {
private:
    double D1, L, t0;
public:
    EllipticalMandrel(double D0, double D1, double L);

    std::complex<double> Radius(const std::complex<double>& t) override;
    std::complex<double> Height(const std::complex<double>& t) override;
};

/*class TangentOgiveMandrel : public AxisymmetricMandrelSegment {
private:
    double D0, D1, L;
public:
    TangentOgiveMandrel(double D0, double D1, double L);

    std::complex<double> Radius(const std::complex<double>& t) override;
    std::complex<double> Height(const std::complex<double>& t) override;
};*/
