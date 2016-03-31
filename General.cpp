//
// Created by strratholm on 31.03.2016.
//

#include "General.h"

int isWithinError(double x, double y, double xError, double yError) {
    if ((x - xError <= y + yError) && (x + xError >= y - yError)) return 1;
    vector<double> hello;
    return 0;
}