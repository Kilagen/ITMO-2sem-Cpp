#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Point{
private:
    float x_;
    float y_;
public:
    Point() = default;
    explicit Point(float x, float y)
            : x_(x)
            , y_(y) {}
    Point(const Point& other)
            : x_(other.x_)
            , y_(other.y_) {}
    ~Point() = default;
    Point operator=(const Point& other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
    float x() const {
        return x_;
    }
    float y() const {
        return y_;
    }
    bool equals(const Point& other) const {
        return other.x_ == x_ && other.y_ == y_;
    }
    float distance(const Point& other) const {
        double distance_ = 0;
        distance_ += (x_ - other.x_) * (x_ - other.x_);
        distance_ += (y_ - other.y_) * (y_ - other.y_);
        return (float) sqrt(distance_);
    }
};

class Line {
protected:
    vector<Point> points_;
    float perimeter_ = 0;
public:
    explicit Line(const vector<Point>& points)
            : points_(points) {}
    Line(const Line& other)
            : points_(other.points_) {}
    ~Line() = default;
    Line& operator=(const Line& other) {
        points_ = other.points_;
        return *this;
    }

    virtual float perimeter()
    {
        if (perimeter_ == 0) {

            Point prev_point = points_.at(0);
            for (const Point &point: points_) {
                if (!prev_point.equals(point)) {
                    perimeter_ += prev_point.distance(point);
                }
                prev_point = point;
            }
        }
        return perimeter_;
    }
    [[nodiscard]] Point getPoint(int index) const {
        return points_.at(index);
    }
    [[nodiscard]] int dotCount() const {
        return points_.size();
    }
};

class LockedLine : public Line {
public:
    explicit LockedLine(const vector<Point>& points)
            : Line(points) {}
    LockedLine(const LockedLine& other) = default;
    ~LockedLine() = default;
    LockedLine& operator=(const LockedLine& other) {
        points_ = other.points_;
        return *this;
    }

    float perimeter() override
    {
        if (perimeter_ == 0) {
            Point prev_point = points_.at(points_.size()-1);
            for (const Point &point: points_) {
                if (!prev_point.equals(point)) {
                    perimeter_ += prev_point.distance(point);
                }
                prev_point = point;
            }
        }
        return perimeter_;
    }
};

class Polygon {
public:

    explicit Polygon(const LockedLine& line)
            : line_(line) {
        for (int i = 0; i < line.dotCount(); i++) {
            Point p1 = line.getPoint(i);
            Point p2 = line.getPoint((i+1) % line.dotCount());
            for (int j = 0; j < i; j++) {
                Point p3 = line.getPoint(j);
                Point p4 = line.getPoint((j+1) % line.dotCount());
                if (check(p1, p2, p3, p4)) {
                    throw invalid_argument("Given line is not a polygon border!");
                }
            }
        }
    }
    Polygon(const Polygon& other)
            : Polygon(other.line_) {}
    ~Polygon() = default;
    Polygon& operator=(const Polygon& other) {
        line_ = other.line_;
        return *this;
    }
    float perimeter()
    {
        return line_.perimeter();
    };

    double area()
    {
        if (area_ == 0) {
            Point prev = line_.getPoint(line_.dotCount()-1);
            for (int i = 0; i < line_.dotCount(); i++) {
                Point next = line_.getPoint(i);
                area_ += prev.x() * next.y() - prev.y() * next.x();
                prev = next;
            }
            if (area_ < 0) {
                area_ = -area_;
            }
            area_ = area_ / 2;
        }
        return area_;
    };
protected:
    bool check(Point a, Point b, Point c, Point d) {
        return false;
    }
    double area_ = 0;
    LockedLine line_;
};

class Triangle : public Polygon {
public:
    explicit Triangle(const LockedLine& line)
            : Polygon(line)
    {
        if (line.dotCount() != 3) {
            throw invalid_argument("Triangle border has to contain exactly 3 points!");
        }
    }
    Triangle(const Triangle& other)
            : Triangle(other.line_) {}
    ~Triangle() = default;
    Triangle& operator=(const Triangle& other) {
        line_ = other.line_;
        return *this;
    }
};

class Trapezoid : public Polygon {
public:
    explicit Trapezoid(const LockedLine& line)
            : Polygon(line)
    {
        if (line.dotCount() == 4) {
            Point p1 = line.getPoint(0);
            Point p2 = line.getPoint(1);
            Point p3 = line.getPoint(2);
            Point p4 = line.getPoint(3);
            if (((p1.x() - p2.x()) * (p3.y() - p4.y()) != (p1.y() - p2.y()) * (p3.x() - p4.x()))
                || ((p4.x() - p1.x()) * (p2.y() - p3.y()) != (p4.y() - p1.y()) * (p2.x() - p3.x()))) {
                throw invalid_argument("Given line is not a trapezoid border!");
            }
        } else {
            throw invalid_argument("Trapezoid border has to contain exactly 4 points!");
        }
    }
    Trapezoid(const Trapezoid& other)
            : Trapezoid(other.line_) {}
    ~Trapezoid() = default;
    Trapezoid& operator=(const Trapezoid& other) {
        line_ = other.line_;
        return *this;
    }
};

class RegularPolygon : public Polygon {
public:
    explicit RegularPolygon(const LockedLine& line)
            : Polygon(line)
    {
        float x = 0;
        float y = 0;
        float eps = 1e-7;
        for (int i = 1; i < line.dotCount(); i++) {
            Point p = line.getPoint(i);
            x += p.x();
            y += p.y();
        }
        Point center(x / static_cast<float>(line.dotCount()), y / (line.dotCount() * 1.f));
        float dist = line.getPoint(0).distance(center);
        for (int i = 1; i < line.dotCount(); i++) {
            if (fabsf(line.getPoint(i).distance(center) - dist) > eps) {
                throw invalid_argument("Given border is not a regular polygon border");
            }
        }
    }
    RegularPolygon(const Point& center, const Point& point, unsigned int n)
            : Polygon(LockedLine({Point(0, 0)})) //костыль, зато какой!
    {
        if (n < 3) {
            throw invalid_argument("Polygon must have at least 3 points!");
        }
        float x = center.x();
        float y = center.y();
        float theta = atan2f(point.x()-x, point.y()-y);
        if (point.x()-x < 0) {
            theta = -theta;
        }
        float r = sqrtf(pow(point.x()-x, 2) + pow(point.y()-y, 2));
        float pi = 3.14159265359;
        vector<Point> points;
        for (int i = 0; i < n; i++) {
            points.push_back(Point(r * cos(2*pi*i/n) + x, r * sin(2*pi*i/n) + y));
        }
        line_ = LockedLine(points);
    }
    RegularPolygon(const RegularPolygon& other)
            : RegularPolygon(other.line_) {}
    ~RegularPolygon() = default;
    RegularPolygon& operator=(const RegularPolygon& other) {
        line_ = other.line_;
        return *this;
    }
};
