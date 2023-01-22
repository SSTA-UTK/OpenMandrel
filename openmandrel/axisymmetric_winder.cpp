#include "axisymmetric_winder.h"
#include "mandrel.h"
#include "winder.h"





AxisymmetricWinder::AxisymmetricWinder(double BandWidth,int NumberOfPoints=15) {
    this->NumberOfPoints = NumberOfPoints;
    this->BandWidth = BandWidth;
}


double AxisymmetricWinder::getWindAngle(int T0, int T1) {
    return windAngle;
}

void AxisymmetricWinder::setClairaultRelation(AxisymmetricMandrelSegment *segment,double t) {
    ClairaultRelation = segment->Radius(t).real() * windAngle;
}

double AxisymmetricWinder::getMinimumRadius(int T0, int T1) {
    // get coords at T0 and T1
    // calculate distance between coordinates on the 
    return 1.;
}


double AxisymmetricWinder::getPitch(double windAngle, AxisymmetricMandrelSegment *segment, double t) {
    // returns the Pitch
    return (PI*segment->Radius(t).real()*2)/(tan(windAngle));
}

void AxisymmetricWinder::setwindAngle(double Angle) {
    windAngle = Angle;
}

// returns the number of circuits required to cover the specific parameter given
int AxisymmetricWinder::getRequiredCircuits(AxisymmetricMandrelSegment *segment, double t) {
    int NumberOfCircuits;
    double Circuits;
    // get the coords in reals
    // calculate diameter between coords
    // use diameter in calculation
    double Diameter = 2*segment->Radius(t).real();
    Circuits = PI * Diameter * cos(windAngle) / BandWidth;
    
    // make sure it rounds up when necessary.
    double test = Circuits - int(Circuits);
    if(test >= 0.5) {
        NumberOfCircuits += 0.5;
    }


    return int(NumberOfCircuits);
}