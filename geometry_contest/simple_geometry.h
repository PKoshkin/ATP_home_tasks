template<class T>
class Point2D {
private:
    T x;
    T y;

public: 
    Point2D(T inX, T inY) : x(inX), y(inY) {}
    template <class otherT>
    Point2D(const Point2D<otherT>& point) : x(point.getX()), y(point.getY()) {}
    Point2D() {}

    T getX() const {
        return x;
    }

    T getY() const {
        return y;
    }

    T setX(T inX) {
        x = inX;
    }

    T setY(T inY) {
        y = inY;
    }

    bool operator==(const Point2D<T>& point) const {
        return (x == point.x) && (y == point.y);
    }

    friend std::ostream& operator<<(std::ostream& out, const Point2D<T>& point) {
        out << "(" << point.getX() << ", " << point.getY() << ")";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Point2D<T>& point) {
        T x, y;
        in >> x >> y;
        point.setX(x);
        point.setY(y);
        return in;
    }
};

// Это радиус вектор, хранящий координаты своего конца
template <class T>
class Vector2D {
private:
    Point2D<T> end;

public:
    Vector2D(T inX, T inY) : end(inX, inY) {}
    Vector2D(const Point2D<T>& inBegin, const Point2D<T>& inEnd) : end(inEnd.getX() - inBegin.getX(), inEnd.getY() - inBegin.getY()) {}
    Vector2D(const Point2D<T>& inEnd) : end(inEnd.getX(), inEnd.getY()) {}

    T getX() const {
        return end.getX();
    }

    T getY() const {
        return end.getY();
    }

    double length() const {
        return sqrt(end.getX() * end.getX() + end.getY() * getY());
    }

    Point2D<T> getEnd() {
        return end;
    }

    Vector2D<T> operator*(T alpha) const {
        return Vector2D<T>(end.getX() * alpha, end.getY() * alpha);
    }

    Vector2D<T> operator+(const Vector2D<T>& vector) const {
        return Vector2D<T>(end.getX() + vector.getX(), end.getY() + vector.getY());
    }

    Vector2D<T> operator/(T alpha) const {
        return Vector2D<T>(end.getX() / alpha, end.getY() / alpha);
    }

    T scalarProjection(const Vector2D<T>& vector) const {
        return scalarProduct(*this, vector) / vector.length();
    }

    friend Vector2D operator*(T alpha, const Vector2D<T>& vector) {
        return Vector2D(vector.getX() * alpha, vector.getY() * alpha);
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector2D<T>& vector) {
        out << "<" << vector.getX() << ", " << vector.getY() << ">";
        return out;
    }
};

template <class T>
class Segment2D {
private:
    Point2D<T> begin;
    Point2D<T> end;

public:
    Segment2D(const Point2D<T>& inBegin, const Point2D<T>& inEnd) : begin(inBegin), end(inEnd) {}
    template <class otherT>
    Segment2D(const Segment2D<otherT>& segment) : begin(segment.getBegin()), end(segment.getEnd()) {}
    Segment2D() {};

    bool containsPoint(const Point2D<T>& point) const {
        return (vectorProduct(Vector2D<T>(point, begin), Vector2D<T>(point, end)) == 0) && (scalarProduct(Vector2D<T>(point, begin), Vector2D<T>(point, end)) < 0);
    }

    bool isDegenerate() const {
        return begin == end;
    }

    Point2D<T> getBegin() const {
        return begin;
    }

    Point2D<T> getEnd() const {
        return end;
    }

    Vector2D<T> toVector2D() const {
        return Vector2D<T>(end.getX() - begin.getX(), end.getY() - begin.getY());
    }

    double length() const {
        return diatance(begin, end);
    }

    long long squareLength() const {
        return squareDistance(begin, end);
    }

    Point2D<T> pointProjection(const Point2D<T>& point) const {
        return (Vector2D<T>(begin) + this->toVector2D() / this->length() * Vector2D<T>(begin, point).scalarProjection(this->toVector2D())).getEnd();
    }

    friend std::ostream& operator<<(std::ostream& out, const Segment2D<T>& segment) {
        out << "[" << segment.begin << ", " << segment.end << "]";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Segment2D<T>& segment) {
        in >> segment.begin >> segment.end;
        return in;
    }

};

template <class T>
T scalarProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
    return a.getX() * b.getX() + a.getY() * b.getY();
}

template <class T>
T vectorProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
    return a.getY() * b.getX() - a.getX() * b.getY();
}

template <class T>
class Line2D {
private:
    T A, B, C; // Задаем прямую

public:
    Line2D() {}
    Line2D(T inA, T inB, T inC) : A(inA), B(inB), C(inC) {}
    Line2D(const Segment2D<T>& segment) :
        A(segment.getBegin().getY() - segment.getEnd().getY()),
        B(segment.getBegin().getX() - segment.getEnd().getX()),
        C(-A * segment.getBegin().getX() - B * segment.getBegin().getY()) {

        std::cout << "building line from segment: " << segment << std::endl;

    }

    T getA() const {
        return A;
    }

    T getB() const {
        return B;
    }

    T getC() const {
        return C;
    }

    bool operator==(const Line2D<T>& line) const {
        return (A == line.A) && (B == line.B) && (C == line.C);
    }

    friend std::ostream& operator<<(std::ostream& out, const Line2D<T>& line) {
        out << "(" << line.A << " " << line.B << " " << line.C << ")";
        return out;
    }

    friend bool intersect(const Line2D<T> line1, const Line2D<T> line2) {
        if (line1 == line2) {
            return true;
        }
        return (line1.getA() * line2.getC() == line1.getC() * line2.getA()) && (line1.getA() * line2.getB() == line1.getB() * line2.getA());
    }

    friend Point2D<double> intersection(const Line2D<T> line1, const Line2D<T> line2) {
        //double x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
        //double y = (C1 * A2 - A1 * C2) / (A1 * B2 - A2 * B1);

        return Point2D<double>(
            double(line2.getC() * line1.getB() - line1.getC() * line2.getB()) / (line1.getA() * line2.getB() - line2.getA() * line1.getB()),
            double(line1.getC() * line2.getA() - line1.getA() * line2.getC()) / (line1.getA() * line2.getB() - line2.getA() * line1.getB())
        );
    }
};

template <class T>
class Circle2D {
private:
    Point2D<T> center;
    T radius;
public:
    Circle2D(Point2D<T> inCenter, T inRadius) : center(inCenter), radius(inRadius) {};
    Circle2D() {};

    bool containsPoint(const Point2D<T>& point) {
        return distance(center, point) == radius;
    }

    friend std::ostream& operator<<(std::ostream& out, const Circle2D<T>& circle) {
        out << circle.center << " +- " << circle.radius;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Circle2D<T>& circle) {
        in >> circle.center >> circle.radius;
        return in;
    }
};

template<class T>
double distance(const Point2D<T>& a, const Point2D<T>& b) {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}

template<class T>
T squareDistance(const Point2D<T>& a, const Point2D<T>& b) {
    return (a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY());
}

template <class T>
double distance(const Line2D<T>& line, const Point2D<T>& point) {
    return fabs(line.getA() * point.getX() + line.getB() * point.getY() + line.getC()) / sqrt(line.getA() * line.getA() + line.getB() * line.getB());
}

template <class T>
double distance(const Point2D<T>& point, const Line2D<T>& line) {
    return distance(line, point);
}

template <class T>
double distance(const Point2D<T>& point, const Segment2D<T>& segment) { 
    // Будем рассматривать случаи
    if (segment.isDegenerate()) {
        // Первый случай, когда отрезок вырожден.
        return distance(point, segment.getBegin());
    }
    if (squareDistance(point, segment.getBegin()) >= squareDistance(point, segment.getEnd()) + segment.squareLength()) {
        return distance(point, segment.getEnd());
    } else if (squareDistance(point, segment.getEnd()) >= squareDistance(point, segment.getBegin()) + segment.squareLength()) {
        return distance(point, segment.getBegin());
    } else {
        return distance(Line2D<T>(segment), point);
    }
}

template <class T>
double distance(const Segment2D<T>& segment, const Point2D<T>& point) { 
    return distance(point, segment);
}

template <class T>
bool intersect(const Segment2D<T> segment1, const Segment2D<T> segment2) {
    Line2D<T> line1(segment1), line2(segment2);

    std::cout << line1 << " " << line2 << std::endl;

    if (intersect(line1, line2)) {
        
        std::cout << "false type 1" << std::endl;

        return true;
    } else {
        // Разбираем случаи вырожденных отрезков
        if (segment1.isDegenerate() && segment2.isDegenerate()) {
            return segment1.getEnd() == segment2.getEnd();
        } else if (segment1.isDegenerate()) {
            return segment2.containsPoint(segment1.getEnd());
        } else if (segment2.isDegenerate()) {
            return segment1.containsPoint(segment2.getEnd());
        }

        // Основной слуай. Точка пересечения прямых, образованных отрезками должна принадлежать обоим отрезкам
        Point2D<double> linesIntersection = intersection(line1, line2);
        //Segment2D<double> segment1F(segment1), segment2F(segment2);
        
        std::cout << "intersection: " << linesIntersection << std::endl;

        if (scalarProduct(Vector2D<T>(segment1.getBegin(), linesIntersection), Vector2D<T>(segment1.getEnd(), linesIntersection)) < 0) {
            return true;
        }
        if (scalarProduct(Vector2D<T>(segment2.getBegin(), linesIntersection), Vector2D<T>(segment2.getEnd(), linesIntersection)) < 0) {
            return true;
        }

        std::cout << "normal NO" << std::endl;

        return false;
        
        //return segment1F.containsPoint(linesIntersection) && segment2F.containsPoint(linesIntersection);
    }
}
