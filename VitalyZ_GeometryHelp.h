//
// Created by strratholm on 31.03.2016.
//

#ifndef TRIANGLES_GEOMETRYHELP_H
#define TRIANGLES_GEOMETRYHELP_H

#include "VitalyZ_Line.h"
#include <vector>

using namespace std;

typedef vector<VitalyZ::Vector3> VectorsSet;

namespace VitalyZ {

    bool isTrianglesIntersect(VectorsSet triangle1, VectorsSet triangle2);

    bool isTrianglesIntersect(double triangle1[9], double triangle2[9]);
}
#endif //TRIANGLES_GEOMETRYHELP_H
