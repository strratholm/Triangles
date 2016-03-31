#include <iostream>
#include <math.h>
#include <vector>
#include "Vector3.h"
#include "Line.h"

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
