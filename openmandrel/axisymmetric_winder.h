#pragma once


class AxisymmetricWinder {
    public:

        Vec2 calcWoundMandrelSegment(AxisymmetricMandrelSegment &segment);
        AxisymmetricWinder(int NumberOfPoints=15);
    private:
        Vec2 C;
        Quadrature integral;
        Vec3 WindPosition;
        double getWindAngle(int T0, int T1);
        double getMinimumRadius(int T0, int T1);
        int DiscretePoints;
        double WindingAngle; // alpha
        double BandWidth; // B
        double getPitch(double WindAngle, double MandrelDiameter); // P
        void setWindingAngle(double Angle); // alpha
        int requiredCircuits; // N
        int getRequiredCircuits(AxisymmetricMandrelSegment &segment);

};

AxisymmetricWinder::AxisymmetricWinder(int NumberOfPoints=15,double Width) {
    DiscretePoints = NumberOfPoints;
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

int AxisymmetricWinder::getRequiredCircuits(AxisymmetricMandrelSegment &segment, int parameter) {
    //double Diameter = complex(2) *segment.Radius(parameter);
}