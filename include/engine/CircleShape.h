#pragma once
#include "Shape.h"
#include "Point2D.h"

class CircleShape : public Shape {
public:
    Point2D center;
    int radius;
    bool filled = false; // чи заповнювати коло

    CircleShape(Point2D c, int r, Color col);
    void draw(Renderer& r) override;
    void toggleFill(); // метод для перемикання
};