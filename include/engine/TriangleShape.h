#pragma once
#include "Shape.h"
#include "Point2D.h"
#include <array>

class TriangleShape : public Shape {
public:
    Point2D center;
    float size;
    float angle = 0.0f;
    float hue = 0.0f;

    TriangleShape(Point2D c, float s, Color col);
    void draw(Renderer& r) override;
    void update(); // обертання і зміна кольору
};