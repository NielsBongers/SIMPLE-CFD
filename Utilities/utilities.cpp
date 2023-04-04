#include "SIMPLE.h"

double SIMPLE::takeMax(double A, double B) {
    double max = A; 
    if (B > max) {
        max = B;
    }
    return max;
}

double SIMPLE::takeMax(double A, double B, double C) {
    double max = A; 
    if (B > max) {
        max = B;
    }

    if (C > max) {
        max = C;
    }

    return max;
}