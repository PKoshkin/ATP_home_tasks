#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "simple_geometry.h"

int main() {
    typedef Point2D<int> Point;
    typedef Vector2D<int> Vector;

    int N;
    std::vector<Point> points;

    std::ifstream fileIn("polygon.in", std::ifstream::in);
    std::ofstream fileOut("polygon.out", std::ofstream::out);
    fileOut.precision(17);
    fileIn >> N;

    for (int i = 0; i < N; ++i) {
        Point point;
        fileIn >> point;
        points.push_back(point);
    }
    points.push_back(points[0]);
    points.push_back(points[1]);

    bool signIsKnown = false, result = true, isPositive;

    for (int i = 0; i < N; ++i) {
        if (!signIsKnown) {
            if (vectorProduct(Vector(points[i], points[i + 1]), Vector(points[i + 1], points[i + 2])) != 0) {
                isPositive = vectorProduct(Vector(points[i], points[i + 1]), Vector(points[i + 1], points[i + 2])) > 0;
                signIsKnown = true;
            }
            continue;
        }
        
        if ((isPositive != (vectorProduct(Vector(points[i], points[i + 1]), Vector(points[i + 1], points[i + 2])) > 0)) &&
                (vectorProduct(Vector(points[i], points[i + 1]), Vector(points[i + 1], points[i + 2])) != 0)) {
            result = false;
            break;
        }
    }

    fileOut << (result ? "YES" : "NO");

    fileIn.close();
    fileOut.close();
    return 0;
}
