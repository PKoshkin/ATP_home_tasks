#include <iostream>
#include <fstream>

int main() {
    double A1, A2, B1, B2, C1, C2;
    std::ifstream fileIn("intersec1.in", std::ifstream::in);
    fileIn >> A1 >> B1 >> C1 >> A2 >> B2 >> C2;
    fileIn.close();

    double x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
    double y = (C1 * A2 - A1 * C2) / (A1 * B2 - A2 * B1);

    std::ofstream fileOut("intersec1.out", std::ofstream::out);
    fileOut.precision(17);
    fileOut << x << " " << y << std::endl;
    fileOut.close();

    return 0;
}
