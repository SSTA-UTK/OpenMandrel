#pragma once


class AxisymmetricWinder {
    public:

        Vec2 calcWoundMandrelSegment(AxisymmetricMandrelSegment &segment);
        AxisymmetricWinder(double BandWidth,int NumberOfPoints=15);
    private:
        Vec2 C;
        Quadrature integral;
        Vec3 WindPosition;
        double getWindAngle(int T0, int T1);
        double getMinimumRadius(int T0, int T1);
        int NumberOfPoints;
        double WindingAngle; // alpha
        double BandWidth; // B
        double getPitch(double WindAngle, double MandrelDiameter); // P
        void setWindingAngle(double Angle); // alpha
        int requiredCircuits; // N
        std::complex<double> getRequiredCircuits(AxisymmetricMandrelSegment &segment, int parameter);

};

