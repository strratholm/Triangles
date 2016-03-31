#include <iostream>
#include <vector>
#include <math.h>

#define eps 0.0001

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}

int isWithinError(double x, double y, double xError, double yError) {
    if ((x - xError <= y + yError) && (x + xError >= y - yError)) return 1;
    return 0;
}

class Vector3 {
public:
    double x, y, z;

    Vector3(double xx, double yy, double zz) {
        x = xx;
        y = yy;
        z = zz;
    }

    Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }

    double getMagnitude() const{
        double res = sqrt(x*x + y*y + z*z);
        return res;
    }

    Vector3 projectionTo(const Vector3 &other) const{
        double product = Vector3::scalarProduct(*this, other);
        return Vector3(other*(product/pow(other.getMagnitude(), 2)));
    }

    Vector3 normalize() const {
        return (*this)*(1./getMagnitude());
    }

    Vector3 operator-() const {
        return Vector3(-x,-y,-z);
    }

    Vector3 operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(double a) const {
        return Vector3(x*a, y*a, z*a);
    }

    static double cosBetween(const Vector3 &vect1, const Vector3 &vect2) {
         return Vector3::scalarProduct(vect1, vect2)/(vect1.getMagnitude()*vect2.getMagnitude());
    }

    static Vector3 crossProduct(const Vector3 &vect1, const Vector3 &vect2) {
        return Vector3(vect1.y*vect2.z - vect1.z*vect2.y,
                       vect1.z*vect2.x - vect1.x*vect2.z,
                       vect1.x*vect2.y - vect1.y*vect2.x);
    }

    static double scalarProduct(const Vector3 &vect1, const Vector3 &vect2) {
        double res = vect1.x*vect2.x + vect1.y*vect2.y + vect1.z*vect2.z;
        return res;
    }

    static bool isCollinear(const Vector3 &vect1, const Vector3 &vect2) {
        if (isWithinError(vect1.getMagnitude(), 0, eps, 0) || isWithinError(vect2.getMagnitude(), 0, eps, 0))
            return true;

        if ((isWithinError(vect1.x, 0, eps, 0) && !isWithinError(vect2.x, 0, eps, 0)) ||
                (isWithinError(vect2.y, 0, eps, 0) && !isWithinError(vect1.x, 0, eps, 0)))
            return false;
        if ((isWithinError(vect1.y, 0, eps, 0) && !isWithinError(vect2.y, 0, eps, 0)) ||
                (isWithinError(vect2.y, 0, eps, 0) && !isWithinError(vect1.y, 0, eps, 0)))
            return false;
        if ((isWithinError(vect1.z, 0, eps, 0) && !isWithinError(vect2.z, 0, eps, 0)) ||
                (isWithinError(vect2.z, 0, eps, 0) && !isWithinError(vect1.z, 0, eps, 0)))
            return false;

        double alpha[3];
        alpha[0] = vect2.x/vect1.x;
        alpha[1] = vect2.y/vect1.y;
        alpha[2] = vect2.z/vect1.z;

        int alphaComparison = 1;
        for (int i = 0; i < 3; ++i) {
            if (isWithinError(alpha[i], 0, eps, 0)) {
                alphaComparison &= 1;
            } else {
                alphaComparison &= isWithinError(alpha[i], alpha[(i + 1) % 3], eps, eps);
            }
        }

        return alphaComparison != 0;
    }
};


class Line {
public:
    Vector3 dir_vector;
    Vector3 base_point;

    Line(const Plane &pl1, const Plane &pl2) {
        //???????????????????????????????????????????????????????????????????????????????
    }

    Line(const Vector3 &vect, const Vector3 &point) {
        dir_vector = Vector3(vect);
        base_point = Vector3(point);
    }

    static bool isParallel(const Line &line1, const Line &line2) {
        return Vector3::isCollinear(line1.dir_vector, line2.dir_vector);
    }

    static bool isSame(const Line &line1, const Line &line2) {
        if (Line::isParallel(line1, line2)) {
            Vector3 temp_vect = Vector3(line1.base_point - line2.base_point);
            if (Vector3::isCollinear(line1.dir_vector, temp_vect))
                return true;
        }
        return false;
    }

    static Vector3 getIntersection(const Line &line1, const Line &line2) {
        Vector3 dif_to_line1 = (line2.base_point - line1.base_point).projectionTo(line1.dir_vector);
        Vector3 altitude = line2.base_point - line1.base_point - dif_to_line1;

        Vector3 from_base2_to_inter = line2.dir_vector.normalize()*
                (altitude.getMagnitude()/Vector3::cosBetween(altitude, line2.dir_vector));

        return line2.base_point - from_base2_to_inter;
    }
};


class Plane {

public:
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;

    Vector3 normal;
    double d;

    Plane(const Vector3 &point_1, const Vector3 &point_2, const Vector3 &point_3):
            p1(Vector3(point_1)), p2(Vector3(point_2)), p3(Vector3(point_3)) {

        normal = Vector3::crossProduct(Vector3(p2 - p1),Vector3(p3 - p1));
        d = -1. * Vector3::scalarProduct(p1, normal);

    }

    static bool isParallel(const Plane &plane1, const Plane &plane2) {
        return Vector3::isCollinear(plane1.normal, plane2.normal);
    }

    static bool isSame(const Plane &plane1, const Plane &plane2) {
        if (isParallel(plane1, plane2)) {
            if (isWithinError(plane1.normal.getMagnitude() / plane2.normal.getMagnitude(), plane1.d / plane2.d, eps,
                              eps))
                return true;
        }
        return false;
    }
};

int getMiddleIndex(const vector<Vector3> &vects) {
    if (vects.size() != 3)
        return -1;

    for (int i = 0; i < 3; ++i) {
        Vector3 temp_vect1 = vects[i] - vects[(i+1)%3];
        Vector3 temp_vect2 = vects[i] - vects[(i+2)%3];
        if (Vector3::scalarProduct(temp_vect1, temp_vect2) < 0)
            return i;
    }

    return -1;
}

vector<Vector3> lineIntersectsTriangle(const vector<Vector3> &triangle, const Line &line) {
    vector<Vector3> intersection_points = vector<Vector3>();
    for (int i = 0; i < 3; ++i) {
        Line tr_line = Line(Vector3(triangle[i] - triangle[(i+1)%3]), triangle[i]);
        if (!Line::isParallel(tr_line, line)) {
            intersection_points.push_back(Line::getIntersection(tr_line, line));
        }
    }

    if (intersection_points.size() == 3) {
        int middle_index = getMiddleIndex(intersection_points);
        Vector3 temp_vect = intersection_points[middle_index];
        intersection_points.erase(intersection_points.begin() + middle_index);
        intersection_points.insert(intersection_points.begin() + 1, temp_vect);
    }

    return vector<Vector3>(intersection_points);
}

bool isSegmentsIntersect(vector<Vector3> segment1, vector<Vector3> segment2) {
    //fill this
}

bool isSameHalfPlane(const Line &line, const Vector3 &sample_point, const Vector3 &asked_point) {
    Vector3 vect_to_sample = Vector3(sample_point - line.base_point);

    Vector3 vect_to_asked = Vector3(asked_point - line.base_point);

    Vector3 dir_by_sample = Vector3::crossProduct(line.dir_vector, vect_to_sample);
    Vector3 dir_by_asked = Vector3::crossProduct(line.dir_vector, vect_to_asked);

    if(!Vector3::isCollinear(dir_by_asked, dir_by_sample))
        return false;

    return Vector3::scalarProduct(dir_by_asked, dir_by_sample) <= 0;

}

bool isInTriangle(const vector<Vector3> &triangle, const Vector3 &point) {
    bool test = true;
    for (int i = 0; i < 3; ++i) {
        test &= isSameHalfPlane(Line(Vector3(triangle[i] - triangle[(i+1)%3]), triangle[i]), triangle[(i+2)%3], point);
    }
    return test;
}

bool isTrianglesIntersect(vector<Vector3> triangle1, vector<Vector3> triangle2) {
    Plane plane1 = Plane(triangle1[0], triangle1[1], triangle2[2]);
    Plane plane2 = Plane(triangle2[0], triangle2[1], triangle2[2]);

    if (Plane::isParallel(plane1, plane2)) {
        if (Plane::isSame(plane1, plane2)) {
            bool result = false;
            for (int i = 0; i < 3; ++i) {
                result |= isInTriangle(triangle1, triangle2[i]);
                result |= isInTriangle(triangle2, triangle1[i]);
            }
            return result;
        } else
            return false;
    }

    Line intersection_line = Line(plane1, plane2);

    vector<Vector3> intersection_points1 = lineIntersectsTriangle(triangle1, intersection_line;
    vector<Vector3> intersection_points2 = lineIntersectsTriangle(triangle2, intersection_line);

    if (intersection_points1.size() == 0 || intersection_points2.size() == 0)
        return false;

    return isSegmentsIntersect(intersection_points1, intersection_points2);
}