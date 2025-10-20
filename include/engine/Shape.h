#pragma once
#include "Color.h"
#include "Renderer.h"

class Shape {
public:
    Color color;
    Shape(Color c) : color(c) {}
    virtual void draw(Renderer& renderer) = 0;
};
