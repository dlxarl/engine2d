#pragma once
#include "Shape.h"
#include "Point2D.h"
#include "Transform.h"

class CircleShape : public Shape, public Transform {
public:
    Point2D center;
    int radius;
    bool filled = false;

    CircleShape(Point2D c, int r, Color col);
    void draw(Renderer& r) override;
    void toggleFill();
};