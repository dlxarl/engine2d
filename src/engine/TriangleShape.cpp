#include "TriangleShape.h"
#include "LineShape.h"
#include <cmath>

TriangleShape::TriangleShape(Point2D c, float s, Color col)
    : Shape(col), center(c), size(s) {}

void TriangleShape::update() {
    angle += 0.02f;
    hue += 0.5f;
    if (hue > 360.0f) hue -= 360.0f;

    // Перетворення HSL → RGB (спрощено через синус)
    float r = std::abs(std::sin(hue * 0.01745f));
    float g = std::abs(std::sin((hue + 120) * 0.01745f));
    float b = std::abs(std::sin((hue + 240) * 0.01745f));
    color = Color(r * 255, g * 255, b * 255);
}

void TriangleShape::draw(Renderer& r) {
    Point2D v[3];
    for (int i = 0; i < 3; ++i) {
        float a = angle + i * 2.0f * M_PI / 3.0f;
        v[i] = Point2D(
            center.x + std::cos(a) * size,
            center.y + std::sin(a) * size
        );
    }

    LineShape side1(v[0], v[1], color);
    LineShape side2(v[1], v[2], color);
    LineShape side3(v[2], v[0], color);

    side1.draw(r);
    side2.draw(r);
    side3.draw(r);
}