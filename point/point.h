#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
public:
    float x, y;

    Point(float x = 0, float y = 0);

    Point operator+(const Point &p) const;
    Point operator-(const Point &p) const;
    float length() const;
};

#endif // POINT_H
