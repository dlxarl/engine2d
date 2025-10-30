#pragma once
#include "Shape.h"
#include "Point2D.h"

class CircleShape : public Shape {
public:
    Point2D center;
    int radius;
    bool filled = false;

    CircleShape(Point2D c, int r, Color col);
    void draw(Renderer& r) override;
    void toggleFill(); // switch
};