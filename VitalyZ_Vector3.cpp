//
// Created by strratholm on 31.03.2016.
//

#include "VitalyZ_Vector3.h"
#include "VitalyZ_General.h"
#include <math.h>

using namespace VitalyZ;

Vector3::Vector3(double xx, double yy, double zz) {
    x = xx;
    y = yy;
    z = zz;
}

double Vector3::getMagnitude() const {
    double hyp1 = hypot(x, y);
    return hypot(hyp1, z);
}

Vector3 Vector3::projectionTo(const Vector3 &other) const {
    double product = Vector3::scalarProduct(*this, other);
    return Vector3(other*(product/pow(other.getMagnitude(), 2)));
}

Vector3 Vector3::normalize() const {
    return Vector3(x / getMagnitude(), y / getMagnitude(), z / getMagnitude());
}

Vector3 Vector3::operator-() const {
    return Vector3(-x,-y,-z);
}

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(double a) const {
    return Vector3(x*a, y*a, z*a);
}

double Vector3::cosBetween(const Vector3 &vect1, const Vector3 &vect2) {
    return Vector3::scalarProduct(vect1, vect2)/(vect1.getMagnitude()*vect2.getMagnitude());
}

Vector3 Vector3::crossProduct(const Vector3 &vect1, const Vector3 &vect2) {
    return Vector3(vect1.y*vect2.z - vect1.z*vect2.y,
                   vect1.z*vect2.x - vect1.x*vect2.z,
                   vect1.x*vect2.y - vect1.y*vect2.x);
}

double Vector3::scalarProduct(const Vector3 &vect1, const Vector3 &vect2) { ;
    return vect1.x*vect2.x + vect1.y*vect2.y + vect1.z*vect2.z;
}

bool Vector3::isCollinear(const Vector3 &vect1, const Vector3 &vect2) {
    if (isWithinError(vect1.getMagnitude(), 0, eps, 0) || isWithinError(vect2.getMagnitude(), 0, eps, 0))
        return true;

    Vector3 vect1Norm = vect1.normalize();
    Vector3 vect2Norm = vect2.normalize();


    if ((vect1Norm.x * vect2Norm.x < -eps) ||
        (vect1Norm.y * vect2Norm.y < -eps) ||
        (vect1Norm.z * vect2Norm.z < -eps))
        vect1Norm = vect1Norm * -1;


    return isWithinError(vect1Norm.x, vect2Norm.x, eps, eps) &&
           isWithinError(vect1Norm.y, vect2Norm.y, eps, eps) &&
           isWithinError(vect1Norm.z, vect2Norm.z, eps, eps);

}

bool Vector3::isSame(const Vector3 &vect1, const Vector3 &vect2, double error1, double error2) {
    bool res = isWithinError(vect1.z, vect2.z, error1, error2);
    res &= isWithinError(vect1.x, vect2.x, error1, error2);
    res &= isWithinError(vect1.y, vect2.y, error1, error2);

    return res;
}
