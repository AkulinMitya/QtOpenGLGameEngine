#include "point.h"

Point::Point(float x, float y) : x(x), y(y) {}

Point Point::operator+(const Point &p) const {
    return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point &p) const {
    return Point(x - p.x, y - p.y);
}

float Point::length() const {
    return std::sqrt(x * x + y * y);
}
