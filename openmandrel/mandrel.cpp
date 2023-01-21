#include "mandrel.h"

LinearTransitionMandrel::LinearTransitionMandrel(double D0, double D1, double L) :
    D0(D0),
    D1(D1),
    L(L) { }

std::complex<double> LinearTransitionMandrel::Radius(const std::complex<double>& t) {

}

std::complex<double> LinearTransitionMandrel::Height(const std::complex<double>& t) {

}

PowerSeriesMandrel::PowerSeriesMandrel(double power, double D_base, double h) :
    power(power),
    D_base(D_base),
    h(h) { }

std::complex<double> PowerSeriesMandrel::Radius(const std::complex<double>& t) {

}

std::complex<double> PowerSeriesMandrel::Height(const std::complex<double>& t) {

}
