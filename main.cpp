#include <iostream>
#include <math.h>
#include <vector>
#include <assert.h>
#include "Vector3.h"
#include "Line.h"
#include "GeometryHelp.h"

using namespace std;

class Test {
private:
    vector<Vector3> triangle1;
    vector<Vector3> triangle2;

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
        triangle1 = vector<Vector3>(3);
        triangle2 = vector<Vector3>(3);
    }

    bool in_same_plane_true() {
        fillTriangle(1, Vector3(0,0,0), Vector3(1,0,0), Vector3(0,1,0));
        fillTriangle(2, Vector3(0,0,0), Vector3(-1,2,0), Vector3(1,2,0));

        return isTrianglesIntersect(triangle1, triangle2);
    }

    bool dif_planes() {
        fillTriangle(1, Vector3(1, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1));
        fillTriangle(2, Vector3(0, -1, 0.5), Vector3(0, 1, 0.5), Vector3(1, 0, 0.5));

        return isTrianglesIntersect(triangle1, triangle2);
    }
};

int main() {
    cout << "Hello, World!" << endl;
    Test test = Test();
    assert(test.in_same_plane_true());
    assert(test.dif_planes());

    return 0;
}


