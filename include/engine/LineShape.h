#pragma once
#include "Shape.h"
#include "Point2D.h"

class LineShape : public Shape {
public:
    Point2D p1, p2;

    LineShape(Point2D a, Point2D b, Color c);

    void draw(Renderer& r) override;
};
