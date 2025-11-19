#pragma once
#include "Shape.h"
#include "Transform.h"
#include "Point2D.h"

class TriangleShape : public Shape, public Transform {
public:
    float size;
    float hue = 0.0f;
    bool filled = false;

    TriangleShape(Point2D pos, float s, Color col);

    void draw(Renderer& r) override;
    void toggleFill();
};
