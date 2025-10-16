#pragma once
#include "Shape.h"

class CircleShape : public Shape {
public:
    float radius;

    CircleShape(Point2D pos, float r, Color col)
        : Shape(pos, col), radius(r) {}

    void draw() override {
        al_draw_filled_circle(position.x, position.y, radius,
                              al_map_rgba_f(color.r, color.g, color.b, color.a));
    }
};
