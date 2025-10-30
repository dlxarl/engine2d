#pragma once
#include "Shape.h"
#include "Renderer.h"
#include "Point2D.h"
#include "Color.h"

class RectangleShape : public Shape {
public:
    Point2D pos;
    int width, height;
    Color fillColor;
    Color borderColor;

    RectangleShape(Point2D p, int w, int h, Color fill, Color border = Color(0, 0, 0));
    void draw(Renderer& r) override;
};