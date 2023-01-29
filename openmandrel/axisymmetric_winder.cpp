#include "axisymmetric_winder.h"
#include "mandrel.h"
#include "winder.h"
#include "math.h"





AxisymmetricWinder::AxisymmetricWinder(double BandWidth,int NumberOfPoints=15) {
    this->NumberOfPoints = NumberOfPoints;
    this->BandWidth = BandWidth;
}


double AxisymmetricWinder::getWindAngle(AxisymmetricMandrelSegment *segment, std::pair<double, double> *phi, std::pair<double, double> *alpha_estimate, double *tolerance, pair<double, double> *start) {
    // given a point phi and an angle, approximate what winding angle it would take to get to zero
    // phi is the desired output
    // initial angle "guess" as alpha_estimate parameter
    // acceptable toleranace also a parameter
    unsigned int iterations = 0;
    unsigned int MaxIterations = 1000;
    double WindAngle;
    double alpha; // adjusts this variable depending on the results
    double previous_alpha = solveExitAngle(segment, GAUSS, alpha_estimate);
    do {
        ITERATIONS++;
        // newton's method to solve
        alpha = previous_alpha - 0.001*(solveExitAngle(segment, GAUSS, previous_alpha) - phi)/(solveExitAngle(segment, GAUSS, previous_alpha)-solveExitAngle(segment, GAUSS, previous_alpha - 0.001));
        // break out if the outputs are effectively close enough
        if(fabs(solveExitAngle(segment, GAUSS, alpha) - solveExitAngle(segment, GAUSS, previous_alpha)) < tolerance) {
            break;
        }
        previous_alpha = alpha;
        
    } while(ITERATIONS < MaxIterations);
    // loops a max of 1000 times before returning the estimated angle
    return alpha;

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


// returns the exit angle of the points
double AxisymmetricWinder::solveExitAngle(AxisymmetricMandrelSegment *segment, Type type, std::pair<double, double> *start) {
    //generate quadrature to approximate the path
    Quadrature quad(15,0,1,type);
    std::pair<double,double> phi2 = start; // start at the given point
    double radius = segment->Radius(0);
    for(int i = 0; i < quad.size; i++) {
            t = quad.xw[i].first;
            w = quad.xw[i].second;
            pair<double, double> derivatives = segment->CylindricalDerivatives(t);
            phi2 += w*sqrt(pow(derivatives.first,2) + pow(derivatives.second,2) )/( sqrt(pow(derivatives.first,2) - pow(derivatives.second,2)) );
            radius = segment->Radius(t);  
        }
    // return double value that represents exit angle
    return phi2

}

void AxisymmetricWinder::PathFinder(AxisymmetricMandrelSegment *segment, Type type=GAUSS) {
    // create quadrature
    Quadrature quad(15,0,1,type);
    pair<double,double> phi = <0,0>;
    double radius = segment->Radius(0);
    double alpha = getWindAngle();
    for(int i = 0; i < quad.size; i++) {
        // get pair at index
        t = quad.xw[i].first;
        // use weight
        w = quad.xw[i].second;
        // obtain derivatives for the cylindrical motion
        pair<double, double> derivatives = segment->CylindricalDerivatives(t);
        phi += w*sqrt(pow(derivatives.first,2) + pow(derivatives.second,2) )/( sqrt(pow(derivatives.first,2) - pow(derivatives.second,2)) );
        // the new radius is the radius at the parameter
        radius = segment->Radius(t);
    }
    // returns the pair that the object traveled through
    return phi;
}