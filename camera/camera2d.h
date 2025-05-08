#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "point/Point.h"

class Camera2D {
public:
    Point position;
    float zoom;

    Camera2D() : position(0, 0), zoom(0.5f) {}

    // Преобразование координат с учетом камеры
    Point applyTransform(const Point& p) const {
        return Point((p.x - position.x) * zoom, (p.y - position.y) * zoom);
    }

    void setPosition(const Point& newPos) {
        position = newPos;
    }
};

#endif // CAMERA2D_H
