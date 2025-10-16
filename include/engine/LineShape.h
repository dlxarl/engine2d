#pragma once
#include "Shape.h"

class LineShape : public Shape {
public:
    Point2D end;

    LineShape(Point2D start, Point2D endPoint, Color col)
        : Shape(start, col), end(endPoint) {}

    void draw() override {
        al_draw_line(position.x, position.y, end.x, end.y,
                     al_map_rgba_f(color.r, color.g, color.b, color.a), 2.0f);
    }
};
