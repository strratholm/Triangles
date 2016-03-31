//
// Created by strratholm on 31.03.2016.
//

#include "GeometryHelp.h"

bool isSameHalfPlane(const Line &line, const Vector3 &sample_point, const Vector3 &asked_point) {
    Vector3 vect_to_sample = Vector3(sample_point - line.base_point);

    Vector3 vect_to_asked = Vector3(asked_point - line.base_point);

    Vector3 dir_by_sample = Vector3::crossProduct(line.dir_vector, vect_to_sample);
    Vector3 dir_by_asked = Vector3::crossProduct(line.dir_vector, vect_to_asked);

    if(!Vector3::isCollinear(dir_by_asked, dir_by_sample))
        return false;

    return Vector3::scalarProduct(dir_by_asked, dir_by_sample) <= 0;
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

    vector<Vector3> intersection_points1 = lineIntersectsTriangle(triangle1, intersection_line);
    vector<Vector3> intersection_points2 = lineIntersectsTriangle(triangle2, intersection_line);

    if (intersection_points1.size() == 0 || intersection_points2.size() == 0)
        return false;

    return isSegmentsIntersect(intersection_points1, intersection_points2);
}

bool isSegmentsIntersect(vector<Vector3> segment1, vector<Vector3> segment2) {
    bool res = false;

    vector<Vector3> temp_array = vector<Vector3>(3);
    for (int i = 0; i < 2; ++i) {
        temp_array[0] = segment1[0]; temp_array[1] = segment2[i]; temp_array[2] = segment1[1];
        res |= (getMiddleIndex(temp_array) == 2);
        temp_array.clear();

        temp_array[0] = segment2[0]; temp_array[1] = segment1[i]; temp_array[2] = segment2[1];
        res |= (getMiddleIndex(temp_array) == 2);
        temp_array.clear();
    }

    return res;
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
        setMiddleInMiddle(intersection_points);
    }

    for (int i = 0; i < intersection_points.size() - 1; ++i) {
        if (isInTriangle(triangle, (intersection_points[i] + intersection_points[i+1])*(1./2))) {
            vector<Vector3> res = vector<Vector3>(2);
            res[0] = intersection_points[i];
            res[1] = intersection_points[i+1];

            return vector<Vector3>(res);
        }
    }

    return vector<Vector3>();
}

void setMiddleInMiddle(vector<Vector3> &vect) {
    int middle_index = getMiddleIndex(vect);
    Vector3 temp_vect = vect[middle_index];
    vect.erase(vect.begin() + middle_index);
    vect.insert(vect.begin() + 1, temp_vect);
}

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

bool isInTriangle(const vector<Vector3> &triangle, const Vector3 &point) {
    bool test = true;
    for (int i = 0; i < 3; ++i) {
        test &= isSameHalfPlane(Line(Vector3(triangle[i] - triangle[(i+1)%3]), triangle[i]), triangle[(i+2)%3], point);
    }
    return test;
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