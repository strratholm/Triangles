//
// Created by strratholm on 31.03.2016.
//

#include "Plane.h"

Plane::Plane(const Vector3 &point_1, const Vector3 &point_2, const Vector3 &point_3)
        : p1(Vector3(point_1)), p2(Vector3(point_2)), p3(Vector3(point_3)) {

    normal = Vector3::crossProduct(Vector3(p2 - p1),Vector3(p3 - p1));
    d = -1. * Vector3::scalarProduct(p1, normal);

}

bool static Plane::isParallel(const Plane &plane1, const Plane &plane2) {
    return Vector3::isCollinear(plane1.normal, plane2.normal);
}

bool static Plane::isSame(const Plane &plane1, const Plane &plane2) {
    if (isParallel(plane1, plane2)) {
        if (isWithinError(plane1.normal.getMagnitude() / plane2.normal.getMagnitude(), plane1.d / plane2.d, eps,
                          eps))
            return true;
    }
    return false;
}