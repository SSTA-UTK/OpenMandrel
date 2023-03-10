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
        double solveExitAngle(AxisymmetricMandrelSegment *segment, Type type, std::pair<double, double> *start);
        std::pair<double,double> PathFinder(AxisymmetricMandrelSegment *segment, Type type=GAUSS); // returns coordinate of next point on geodesic
    private:
        Vec2 C;
        Quadrature integral;
        Vec3 windPosition;
        double ClairaultRelation; // NOTE: might cause issues later with rounding errors
        int NumberOfPoints;
        double windAngle; // alpha
        double BandWidth; // B
        int requiredCircuits; // N
        Vec3 bundleDirection;
        Vec3 bundleBidirection;

};

