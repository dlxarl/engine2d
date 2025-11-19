#pragma once
#include "Point2D.h"
#include <cmath>

class Transform {
public:
    Point2D position;
    float rotation = 0;
    float scaleFactor = 1.0f;

    Transform(const Point2D& pos = Point2D(0,0)) : position(pos) {}

    void move(float dx, float dy) {
        position.x += dx;
        position.y += dy;
    }

    void rotate(float deltaAngle) {
        rotation += deltaAngle;
        if (rotation > 2*M_PI) rotation -= 2*M_PI;
        if (rotation < 0) rotation += 2*M_PI;
    }

    void scale(float factor) {
        scaleFactor *= factor;
        if (scaleFactor < 0.1f) scaleFactor = 0.1f;
        if (scaleFactor > 10.0f) scaleFactor = 10.0f;
    }
};
