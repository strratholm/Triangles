//
// Created by strratholm on 31.03.2016.
//

#ifndef TRIANGLES_PLANE_H
#define TRIANGLES_PLANE_H

#include "VitalyZ_Vector3.h"

namespace VitalyZ {

    class Plane {
    public:
        Vector3 p1;
        Vector3 p2;
        Vector3 p3;

        Vector3 normal;
        double d;

        Plane(const Vector3 &point_1, const Vector3 &point_2, const Vector3 &point_3);

        static bool isParallel(const Plane &plane1, const Plane &plane2);

        static bool isSame(const Plane &plane1, const Plane &plane2);
    };
}

#endif //TRIANGLES_PLANE_H
