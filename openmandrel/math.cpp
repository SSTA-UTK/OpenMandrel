#include "math.h"

#include <iostream>

// Quadrature definitions
// Port of lgwt.m by Greg von Winckel, N is truncation order (number of samples)
std::pair<double, double>* GuassQuadratureGenerator(int N, double r0, double r1) {
    N = N-1;
    int N1 = N+1;
    int N2 = N+2;

    std::pair<double, double>* xw = new std::pair<double, double>[N1];
    double* y  = new double[N1];
    double* y0 = new double[N1];
    double* Lp = new double[N1];
    double* L  = new double[N1*N2];
    double eps = pow(2.0, -52.0);

    for (int i = 0; i < N1*N2; ++i) L[i] = 0.0;
    for (int i = 0; i < N1; ++i) {
        double xu = static_cast<double>(i)/N*2.0 + 1.0;
        y [i] = cos((2.0*i + 1.0) * PI / (2.0*N + 2.0)) + (0.27/N1) * sin((PI*xu*N) / N2);
        y0[i] = 2.0;
        Lp[i] = 0.0;
        L [i] = 1.0;
    }

    double maxResidual;
    do {
        for (int i = 0; i < N1; ++i) L[i + N1] = y[i];
        for (int k = 2; k < N2; ++k) for (int i = 0; i < N1; ++i)
            L[i+k*N1] = ((2.0*k-1.0)*y[i]*L[i+(k-1)*N1] - (k-1)*L[i+(k-2)*N1]) / k;
        for (int i = 0; i < N1; ++i)
            Lp[i] = N2*(L[i+N*N1]-y[i]*L[i+N1*N1]) / (1.0-y[i]*y[i]);
        maxResidual = 0.0;
        for (int i = 0; i < N1; ++i) {
            y0[i] = y [i];
            y [i] = y0[i] - L[i+N1*N1]/Lp[i];
            double residual = abs(y[i]-y0[i]);
            if (residual > maxResidual)
                maxResidual = residual;
        }
    } while (maxResidual > eps);
    for (int i = 0; i < N1; ++i) xw[i] = std::pair<double, double>(
        (r0*(1.0-y[i]) + r1*(1.0+y[i])) / 2.0,
        (r1-r0) / ((1.0-y[i]*y[i])*Lp[i]*Lp[i]) * pow(static_cast<double>(N2)/N1, 2.0));

    delete[] y;
    delete[] y0;
    delete[] Lp;
    delete[] L;
    return xw;
}

std::pair<double, double>* TrapezoidQuadratureGenerator(int N, double r0, double r1) {
    std::pair<double, double>* xw = new std::pair<double, double>[N];
    for (int i = 0; i < N; ++i)
        xw[i] = std::pair<double, double>(static_cast<double>(i)/(N-1), (i==0||i==N-1)?0.5:1.0);
    return xw;
}

Quadrature::Quadrature(int size, double lowerRange, double upperRange, Type type) :
    type(type),
    size(size),
    xw(nullptr) {
    switch (type) {
    case Type::GUASS:
        xw = GuassQuadratureGenerator(size, lowerRange, upperRange);
        break;
    case Type::TRAPEZOID:
        xw = TrapezoidQuadratureGenerator(size, lowerRange, upperRange);
        break;
    default:
        std::cerr << "Unknown quadrature!" << std::endl;
        break;
    }
}

Quadrature::~Quadrature() {
    if (xw == nullptr) return;
    delete[] xw;
}
