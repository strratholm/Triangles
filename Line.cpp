//
// Created by strratholm on 31.03.2016.
//

#include "Line.h"

Line::Line(const Plane &pl1, const Plane &pl2) {
    //???????????????????????????????????????????????????????????????????????????????
}

Line::Line(const Vector3 &vect, const Vector3 &point) {
    dir_vector = Vector3(vect);
    base_point = Vector3(point);
}

bool static Line::isParallel(const Line &line1, const Line &line2) {
    return Vector3::isCollinear(line1.dir_vector, line2.dir_vector);
}

bool static Line::isSame(const Line &line1, const Line &line2) {
    if (Line::isParallel(line1, line2)) {
        Vector3 temp_vect = Vector3(line1.base_point - line2.base_point);
        if (Vector3::isCollinear(line1.dir_vector, temp_vect))
            return true;
    }
    return false;
}

Vector3 static Line::getIntersection(const Line &line1, const Line &line2) {
    Vector3 dif_to_line1 = (line2.base_point - line1.base_point).projectionTo(line1.dir_vector);
    Vector3 altitude = line2.base_point - line1.base_point - dif_to_line1;

    Vector3 from_base2_to_inter = line2.dir_vector.normalize()*
                                  (altitude.getMagnitude()/Vector3::cosBetween(altitude, line2.dir_vector));

    return line2.base_point - from_base2_to_inter;
}