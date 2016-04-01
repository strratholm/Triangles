//
// Created by strratholm on 31.03.2016.
//

#include <assert.h>
#include "Line.h"

Line::Line(const Plane &pl1, const Plane &pl2) {
    dir_vector = Vector3::crossProduct(pl1.normal, pl2.normal);

    int ind1, ind2;
    if (dir_vector.x != 0) {
        ind1 = 1; ind2 = 2; base_point.x = 0;
    } else if (dir_vector.y != 0) {
        ind1 = 0; ind2 = 2; base_point.y = 0;
    } else {
        ind1 = 0; ind2 = 1; base_point.z = 0;
    }

    double coordpl[2][3] = {{pl1.normal.x, pl1.normal.y, pl1.normal.z}, {pl2.normal.x, pl2.normal.y, pl2.normal.z}};

    double coords[2];

    int jind1, jind2;

    jind1 = (coordpl[0][ind1] != 0) ? 0 : 1;
    jind2 = (jind1 + 1) % 2;

    coords[1] = (pl1.d*coordpl[jind2][ind1]/coordpl[jind1][ind1] - pl2.d)/
            (coordpl[jind2][ind2] - coordpl[jind1][ind2]*coordpl[jind2][ind1]/coordpl[jind1][ind1]);

    coords[0] = (-pl1.d - coordpl[jind1][ind2])/coordpl[jind1][ind1];

    setBasePointCoords(ind1, ind2, coords[0], coords[1]);
}

Line::Line(const Vector3 &vect, const Vector3 &point) {
    dir_vector = Vector3(vect);
    base_point = Vector3(point);
}

bool Line::isParallel(const Line &line1, const Line &line2) {
    return Vector3::isCollinear(line1.dir_vector, line2.dir_vector);
}

bool Line::isSame(const Line &line1, const Line &line2) {
    if (Line::isParallel(line1, line2)) {
        Vector3 temp_vect = Vector3(line1.base_point - line2.base_point);
        if (Vector3::isCollinear(line1.dir_vector, temp_vect))
            return true;
    }
    return false;
}

Vector3 Line::getIntersection(const Line &line1, const Line &line2) {
    if (isWithinError(line1.base_point.x, line2.base_point.x, eps, eps) &&
                isWithinError(line1.base_point.y, line2.base_point.y, eps, eps) &&
                isWithinError(line1.base_point.z, line2.base_point.z, eps, eps)) {
        return Vector3(line1.base_point);
    }

    Vector3 dif_to_line1 = (line2.base_point - line1.base_point).projectionTo(line1.dir_vector);
    Vector3 altitude = line2.base_point - line1.base_point - dif_to_line1;

    Vector3 from_base2_to_inter;
    double cos = Vector3::cosBetween(altitude, line2.dir_vector);
    if (!isWithinError(altitude.getMagnitude(), 0, eps, 0)) {
        from_base2_to_inter = line2.dir_vector.normalize() *
                                      (altitude.getMagnitude() / cos);
    } else
        from_base2_to_inter = Vector3();

    return line2.base_point - from_base2_to_inter;
}

void Line::setBasePointCoords(int ind1, int ind2, double val1, double val2) {
    switch (ind1) {
        case 0:
            base_point.x = val1;
            break;
        case 1:
            base_point.y = val1;
            break;
        case 2:
            base_point.z = val1;
            break;
        default:
            return;
    }

    switch (ind2) {
        case 0:
            base_point.x = val2;
            break;
        case 1:
            base_point.y = val2;
            break;
        case 2:
            base_point.z = val2;
            break;
        default:
            return;
    }
}
