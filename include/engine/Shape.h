#pragma once
#include <allegro5/allegro_primitives.h>
#include "Point2D.h"

struct Color {
    float r, g, b, a;
};

class Shape {
public:
    Point2D position;
    Color color;

    Shape(Point2D pos, Color col) : position(pos), color(col) {}
    virtual void draw() = 0;
    virtual ~Shape() = default;
};
