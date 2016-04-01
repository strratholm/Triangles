//
// Created by strratholm on 31.03.2016.
//

#include "Vector3.h"


Vector3::Vector3(double xx, double yy, double zz) {
    x = xx;
    y = yy;
    z = zz;
}

double Vector3::getMagnitude() const {
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::projectionTo(const Vector3 &other) const {
    double product = Vector3::scalarProduct(*this, other);
    return Vector3(other*(product/pow(other.getMagnitude(), 2)));
}

Vector3 Vector3::normalize() const {
    return (*this)*(1./getMagnitude());
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

    if ((isWithinError(vect1.x, 0, eps, 0) && !isWithinError(vect2.x, 0, eps, 0)) ||
        (isWithinError(vect2.x, 0, eps, 0) && !isWithinError(vect1.x, 0, eps, 0)))
        return false;
    if ((isWithinError(vect1.y, 0, eps, 0) && !isWithinError(vect2.y, 0, eps, 0)) ||
        (isWithinError(vect2.y, 0, eps, 0) && !isWithinError(vect1.y, 0, eps, 0)))
        return false;
    if ((isWithinError(vect1.z, 0, eps, 0) && !isWithinError(vect2.z, 0, eps, 0)) ||
        (isWithinError(vect2.z, 0, eps, 0) && !isWithinError(vect1.z, 0, eps, 0)))
        return false;

    double alpha[3] = {false, false, false};
    bool doAlpha[3] = {0, 0, 0};
    if (vect1.x != 0) {
        alpha[0] = vect2.x/vect1.x;
        doAlpha[0] = true;
    }
    if (vect1.y != 0) {
        alpha[1] = vect2.y/vect1.y;
        doAlpha[1] = true;
    }
    if (vect1.z != 0) {
        alpha[2] = vect2.z/vect1.z;
        doAlpha[2] = true;
    }

    bool alphaComparison = true;
    for (int i = 0; i < 3; ++i) {
        if (!doAlpha[i] || !doAlpha[(i + 1) % 3]) {
            alphaComparison &= true;
        } else {
            alphaComparison &= isWithinError(alpha[i], alpha[(i + 1) % 3], eps, eps);
        }
    }

    return alphaComparison;
}