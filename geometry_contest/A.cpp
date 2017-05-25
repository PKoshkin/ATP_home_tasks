#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

class Vector2D;

class Point {
private:
    double x;
    double y;

public:
    Point(double inX, double inY);
    Point(const Point& point);
    Point(const Vector2D& vector);
    Point();
    double getX() const;
    double getY() const;
    double setX(double inX);
    double setY(double inY);
    Point operator+(const Vector2D& vector) const;
    bool operator==(const Point& point) const;
    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend std::istream& operator>>(std::istream& in, Point& point);
};

class Segment {
private:
    Point begin;
    Point end;

public:
    Segment(Point inBegin, Point inEnd);
    bool containsPoint(const Point& point) const;
    Vector2D toVector2D() const;
    double length() const;
    Point pointProjection(const Point& point) const;
};

class Vector2D {
private:
    double x;
    double y;
public:
    Vector2D(double inX, double inY);
    Vector2D(Point begin, Point end);
    double getX() const;
    double getY() const;
    double length() const;
    double scalarProjection(const Vector2D& vector) const;
    friend double scalarProduct(const Vector2D& a, const Vector2D& b);
    friend double vectorProduct(const Vector2D& a, const Vector2D& b);
    Vector2D operator*(double alpha) const;
    Vector2D operator/(double alpha) const;
    friend Vector2D operator*(double alpha, const Vector2D& vector);
    friend std::ostream& operator<<(std::ostream& out, const Vector2D& vector);
};

double scalarProduct(const Vector2D& a, const Vector2D& b) {
    return a.x * b.x + a.y * b.y;
}

double vectorProduct(const Vector2D& a, const Vector2D& b) {
    return a.getY() * b.getX() - a.getX() * b.getY();
}

double distance(Point a, Point b) {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}

Point::Point(double inX, double inY) : x(inX), y(inY) {}

Point::Point(const Point& point) : x(point.x), y(point.y) {}

Point::Point(const Vector2D& vector) : x(vector.getX()), y(vector.getY()) {}

Point::Point() {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

double Point::setX(double inX) {
    x = inX;
}

double Point::setY(double inY) {
    y = inY;
}

Point Point::operator+(const Vector2D& vector) const {
    return Point(x + vector.getX(), y + vector.getY());
}

bool Point::operator==(const Point& point) const {
    return (x == point.x) && (y == point.y);
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.getX() << ", " << point.getY() << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Point& point) {
    double x, y;
    in >> x >> y;
    point.setX(x);
    point.setY(y);
    return in;
}

double Vector2D::getX() const {
    return x;
}

double Vector2D::getY() const {
    return y;
}

double Vector2D::length() const {
    return sqrt(x * x + y * y);
}

Vector2D::Vector2D(double inX, double inY) : x(inX), y(inY) {}

Vector2D::Vector2D(Point begin, Point end) : x(end.getX() - begin.getX()), y(end.getY() - begin.getY()) {}

Vector2D Vector2D::operator*(double alpha) const {
    return Vector2D(x * alpha, y * alpha);
}

Vector2D Vector2D::operator/(double alpha) const {
    return Vector2D(x / alpha, y / alpha);
}

Vector2D operator*(double alpha, const Vector2D& vector) {
    return Vector2D(vector.x * alpha, vector.y * alpha);
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vector) {
    out << "<" << vector.getX() << ", " << vector.getY() << ">";
    return out;
}

double Vector2D::scalarProjection(const Vector2D& vector) const {
    return scalarProduct(*this, vector) / vector.length();
}

Segment::Segment(Point inBegin, Point inEnd) : begin(inBegin), end(inEnd) {}

bool Segment::containsPoint(const Point& point) const {
    return (vectorProduct(Vector2D(point, begin), Vector2D(point, end)) == 0) && (scalarProduct(Vector2D(point, begin), Vector2D(point, end)) < 0);
}

Vector2D Segment::toVector2D() const {
    return Vector2D(end.getX() - begin.getX(), end.getY() - begin.getY());
}

Point Segment::pointProjection(const Point& point) const {
    return begin + this->toVector2D() / this->length() * Vector2D(begin, point).scalarProjection(this->toVector2D());
}

double Segment::length() const {
    return sqrt((end.getX() - begin.getX()) * (end.getX() - begin.getX()) + (end.getY() - begin.getY()) * (end.getY() - begin.getY()));
}

int main() {
    Point A, B, O;

    std::ifstream fileIn("distance4.in", std::ifstream::in);
    fileIn >> O >> A >> B;
    fileIn.close();
    std::ofstream fileOut("distance4.out", std::ofstream::out);
    fileOut.precision(17);

    // Будем рассматривать случаи
    if (A == B) {
        // Первый случай, когда отрезок вырожден.
        fileOut << distance(O, A);
    } else if (vectorProduct(Vector2D(O, A), Vector2D(O, B)) == 0) {
        // Второй случай - когда точка принадлежит прямой, образованной отрезком.
        fileOut << std::min(distance(O, A), distance(O, B));
    } else if (Segment(A, B).containsPoint(Segment(A, B).pointProjection(O))) {
        // Точка проекции принадлежит отрезку
        fileOut << distance(Segment(A, B).pointProjection(O), O);
    } else {
        fileOut << std::min(distance(A, O), distance(B, O));
    }

    fileOut.close();
    return 0;
}
