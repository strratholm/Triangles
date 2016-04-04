#include <vector>
#include <assert.h>
#include "VitalyZ_Vector3.h"
#include "VitalyZ_GeometryHelp.h"

using namespace std;
using namespace VitalyZ;

class Test {
private:
    VectorsSet triangle1;
    VectorsSet triangle2;

    void fillTriangle(int number, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) {
        switch (number) {
            case 1:
                triangle1[0] = Vector3(v1);
                triangle1[1] = Vector3(v2);
                triangle1[2] = Vector3(v3);
                break;
            case 2:
                triangle2[0] = Vector3(v1);
                triangle2[1] = Vector3(v2);
                triangle2[2] = Vector3(v3);
                break;
            default:
                return;
        }
    }
public:
    Test() {
        triangle1 = VectorsSet(3);
        triangle2 = VectorsSet(3);
    }

    bool samePlaneTrue() {
        fillTriangle(1, Vector3(0,0,0), Vector3(1,0,0), Vector3(0,1,0));
        fillTriangle(2, Vector3(0,0,0), Vector3(-1,2,0), Vector3(1,2,0));

        return isTrianglesIntersect(triangle1, triangle2);
    }

    bool samePlaneFalse() {
        fillTriangle(1, Vector3(0,0,0), Vector3(1,0,0), Vector3(0,1,0));
        fillTriangle(2, Vector3(5,5,0), Vector3(6,5,0), Vector3(7,8,0));

        return !isTrianglesIntersect(triangle1, triangle2);
    }

    bool difPlanesTrue() {
        fillTriangle(1, Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1));
        fillTriangle(2, Vector3(0, -1, 0.5), Vector3(0, 1, 0.5), Vector3(1, 0, 0.5));

        return isTrianglesIntersect(triangle1, triangle2);
    }

    bool difPlanesFalse() {
        fillTriangle(1, Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1));
        fillTriangle(2, Vector3(0, -1, 1.5), Vector3(0, 1, 1.5), Vector3(1, 0, 1.5));

        return !isTrianglesIntersect(triangle1, triangle2);
    }

    bool samePlanesCommonVertex() {
        fillTriangle(1, Vector3(1, 1, 0), Vector3(0, 0, 0), Vector3(1, -1, 0));
        fillTriangle(2, Vector3(-1, 1, 0), Vector3(0, 0, 0), Vector3(-1, -1, 0));

        return isTrianglesIntersect(triangle1, triangle2);
    }

    bool difPlanesCommonVertex() {
        fillTriangle(1, Vector3(1, 1, 0), Vector3(0, 0, 0), Vector3(1, -1, 0));
        fillTriangle(2, Vector3(-1, 0, 1), Vector3(0, 0, 0), Vector3(-1, 0, 1));

        return isTrianglesIntersect(triangle1, triangle2);
    }

    bool samePlaneCommonEdge() {
        fillTriangle(1, Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, -1, 0));
        fillTriangle(2, Vector3(-1, 0, 0), Vector3(0, 1, 0), Vector3(0, -1, 0));

        return isTrianglesIntersect(triangle1, triangle2);
    }

    bool difPlaneCommonEdge() {
        fillTriangle(1, Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, -1, 0));
        fillTriangle(2, Vector3(0, 0, 1), Vector3(0, 1, 0), Vector3(0, -1, 0));

        return isTrianglesIntersect(triangle1, triangle2);
    }
};

int main() {
    Test test = Test();
    assert(test.samePlaneTrue());
    assert(test.samePlaneFalse());
    assert(test.difPlanesTrue());
    assert(test.difPlanesFalse());
    assert(test.samePlanesCommonVertex());
    assert(test.difPlanesCommonVertex());
    assert(test.samePlaneCommonEdge());
    assert(test.difPlaneCommonEdge());

    return 0;
}


