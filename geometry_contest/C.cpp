#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "simple_geometry.h"

int main() {
    typedef Point2D<int> Point;
    typedef Vector2D<int> Vector;
    typedef Segment2D<int> Segment;
    typedef Line2D<int> Line;

    std::ifstream fileIn("intersec2.in", std::ifstream::in);
    std::ofstream fileOut("intersec2.out", std::ofstream::out);
    fileOut.precision(17);

    Segment segment1, segment2;
    fileIn >> segment1 >> segment2;

    fileOut << (intersect(segment1, segment2) ? "YES" : "NO");

    fileIn.close();
    fileOut.close();
    return 0;
}
