//
// Created by strratholm on 31.03.2016.
//

#include "General.h"

bool isWithinError(double x, double y, double xError, double yError) {
    return ((x - xError <= y + yError) && (x + xError >= y - yError));
}