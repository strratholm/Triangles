//
// Created by strratholm on 31.03.2016.
//

#ifndef TRIANGLES_LINE_H
#define TRIANGLES_LINE_H


#include "Vector3.h"
#include "Plane.h"

class Line {
public:
    Vector3 dir_vector;
    Vector3 base_point;

    Line(const Plane &pl1, const Plane &pl2);
    Line(const Vector3 &vect, const Vector3 &point);

    static bool isParallel(const Line &line1, const Line &line2);
    static bool isSame(const Line &line1, const Line &line2);
    static Vector3 getIntersection(const Line &line1, const Line &line2);
};


#endif //TRIANGLES_LINE_H
