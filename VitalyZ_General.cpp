//
// Created by strratholm on 31.03.2016.
//

#include "VitalyZ_General.h"

bool VitalyZ::isWithinError(double x, double y, double xError, double yError) {
    return ((x - xError <= y + yError) && (x + xError >= y - yError));
}