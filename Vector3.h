//
// Created by strratholm on 31.03.2016.
//

#ifndef TRIANGLES_VECTOR3_H
#define TRIANGLES_VECTOR3_H

#include "math.h"

class Vector3 {
public:
    double x, y, z;

    Vector3(double xx = 0, double yy = 0, double zz = 0);

    double getMagnitude() const;
    Vector3 projectionTo(const Vector3 &other) const;
    Vector3 normalize() const;

    Vector3 operator-() const;
    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
    Vector3 operator*(double a) const;

    static double cosBetween(const Vector3 &vect1, const Vector3 &vect2);
    static Vector3 crossProduct(const Vector3 &vect1, const Vector3 &vect2);
    static double scalarProduct(const Vector3 &vect1, const Vector3 &vect2);
    static bool isCollinear(const Vector3 &vect1, const Vector3 &vect2);
};


#endif //TRIANGLES_VECTOR3_H
