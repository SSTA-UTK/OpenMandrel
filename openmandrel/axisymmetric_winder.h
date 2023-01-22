#pragma once


class AxisymmetricWinder {
    public:

        Vec2 calcWoundMandrelSegment(AxisymmetricMandrelSegment *segment);
        AxisymmetricWinder(double BandWidth,int NumberOfPoints=15);
        void setClairaultRelation(AxisymmetricMandrelSegment *segment,double t);
        double getPitch(double windAngle, AxisymmetricMandrelSegment *segment, double t); // P
        void setwindAngle(double Angle);
        double getWindAngle(int T0, int T1);
        double getMinimumRadius(int T0, int T1);
        int getRequiredCircuits(AxisymmetricMandrelSegment *segment, double t);
    private:
        Vec2 C;
        Quadrature integral;
        Vec3 WindPosition;
        double ClairaultRelation; // NOTE: might cause issues later with rounding errors
        int NumberOfPoints;
        double windAngle; // alpha
        double BandWidth; // B
        int requiredCircuits; // N

};

