#include "axisymmetric_winder.h"
#include "mandrel.h"





AxisymmetricWinder::AxisymmetricWinder(double Width, int NumberOfPoints=15) {
    this->NumberOfPoints = NumberOfPoints;
    BandWidth = Width;
}


double AxisymmetricWinder::getWindAngle(int T0, int T1) {
    // solve nonlinear differential equation
    // get magnitude of t vector and T vector
    // dot product to obtain angle
    return -1;
}

double AxisymmetricWinder::getMinimumRadius(int T0, int T1) {
    // get coords at T0 and T1
    // calculate distance between coordinates on the 
}

double AxisymmetricWinder::getPitch(double WindingAngle, double MandrelDiameter) {
    // returns the Pitch
    return (PI*MandrelDiameter)/(tan(WindingAngle));
}

void AxisymmetricWinder::setWindingAngle(double Angle) {
    WindingAngle = Angle;
}

std::complex<double> AxisymmetricWinder::getRequiredCircuits(AxisymmetricMandrelSegment &segment, int parameter) {
    std::complex<double> NumberOfCircuits = 2 * PI * segment.Radius(parameter) * cos(WindingAngle) / BandWidth;
    //double Diameter = complex(2) *segment.Radius(parameter);
    return NumberOfCircuits;
}