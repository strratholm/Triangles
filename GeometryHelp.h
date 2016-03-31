//
// Created by strratholm on 31.03.2016.
//

#ifndef TRIANGLES_GEOMETRYHELP_H
#define TRIANGLES_GEOMETRYHELP_H

#include "Line.h"
#include <vector>

int isWithinError(double x, double y, double xError, double yError) {
    if ((x - xError <= y + yError) && (x + xError >= y - yError)) return 1;
    return 0;
}

bool isSameHalfPlane(const Line &line, const Vector3 &sample_point, const Vector3 &asked_point);
bool isInTriangle(const vector<Vector3> &triangle, const Vector3 &point);
int getMiddleIndex(const vector<Vector3> &vects);
void setMiddleInMiddle(vector<Vector3> &vect);
vector<Vector3> lineIntersectsTriangle(const vector<Vector3> &triangle, const Line &line);
bool isSegmentsIntersect(vector<Vector3> segment1, vector<Vector3> segment2);
bool isTrianglesIntersect(vector<Vector3> triangle1, vector<Vector3> triangle2);

#endif //TRIANGLES_GEOMETRYHELP_H
