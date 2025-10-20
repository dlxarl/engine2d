#pragma once
#include "Shape.h"
#include "Point2D.h"

class CircleShape : public Shape {
public:
    Point2D center;
    int radius;
    CircleShape(Point2D c, int r, Color col);
    void draw(Renderer& r) override;
};
