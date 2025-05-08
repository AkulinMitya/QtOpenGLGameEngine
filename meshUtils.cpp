#include "meshUtils.h"

std::vector<Point> createRectangleMesh(float width, float height) {
    std::vector<Point> vertices = {
        { -width / 2, -height / 2 },
        {  width / 2, -height / 2 },
        {  width / 2,  height / 2 },
        { -width / 2,  height / 2 }
    };
    return vertices;
}
