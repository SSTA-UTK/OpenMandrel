#include "axisymmetric_winder.h"
#include "mandrel.h"





Vec2 AxisymmetricWinder::calcWoundMandrelSegment(AxisymmetricMandrelSegment *segment) {
    Vec2 derivatives = *segment.CylindricalDerivatives(1);

    return e;

}