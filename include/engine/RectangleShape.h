#pragma once
#include "Shape.h"

class RectangleShape : public Shape {
public:
    float width, height;

    RectangleShape(Point2D pos, float w, float h, Color col)
        : Shape(pos, col), width(w), height(h) {}

    void draw() override {
        al_draw_filled_rectangle(position.x, position.y,
                                 position.x + width, position.y + height,
                                 al_map_rgba_f(color.r, color.g, color.b, color.a));
    }
};
