#pragma once
#include "Shape.h"
#include "Renderer.h"
#include "Point2D.h"
#include "Color.h"
#include "Transform.h"

class RectangleShape : public Shape, public Transform {
public:
    Point2D pos;
    int width, height;

    Color fillColor;
    Color borderColor;

    bool filled = false;

    RectangleShape(Point2D p, int w, int h, Color border);

    void toggleFill();
    void draw(Renderer& r) override;
};
