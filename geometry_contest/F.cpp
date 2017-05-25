#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>

#include "simple_geometry.h"

int main() {
    typedef Point2D<int> Point;

    int N;
    std::vector<Point> points;

    std::ifstream fileIn("area.in", std::ifstream::in);
    std::ofstream fileOut("area.out", std::ofstream::out);
    fileOut.precision(17);

    fileIn >> N;

    long long result = 0;
    for (int i = 0; i < N; ++i) {
        Point point;
        fileIn >> point;
        points.push_back(point);
    }
    points.push_back(points[0]);

    for (int i = 0; i < N; ++i) {
        result += (points[i].getX() - points[i + 1].getX()) * (points[i].getY() + points[i + 1].getY());
    }
    fileOut << fabs(double(result)) / 2;

    fileIn.close();
    fileOut.close();
    return 0;
}
