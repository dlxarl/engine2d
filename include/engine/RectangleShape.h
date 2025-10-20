#pragma once
#include "Shape.h"
#include "Point2D.h"

class RectangleShape : public Shape {
public:
    Point2D pos;
    int width, height;
    RectangleShape(Point2D p, int w, int h, Color c);
    void draw(Renderer& r) override;
};