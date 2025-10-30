#include "TriangleShape.h"
#include "LineShape.h"
#include <cmath>

TriangleShape::TriangleShape(Point2D c, float s, Color col)
    : Shape(col), center(c), size(s) {}

void TriangleShape::toggleFill() {
    filled = !filled;
}

void TriangleShape::update() {
    angle += 0.02f;
    hue += 0.5f;
    if (hue > 360.0f) hue -= 360.0f;

    // HSL -> RGB
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

    if (filled) {
        // Triangle fill
        int minY = std::min({v[0].y, v[1].y, v[2].y});
        int maxY = std::max({v[0].y, v[1].y, v[2].y});

        for (int y = minY; y <= maxY; ++y) {
            std::vector<int> nodes;
            for (int i = 0; i < 3; ++i) {
                Point2D p1 = v[i];
                Point2D p2 = v[(i + 1) % 3];
                if ((p1.y < y && p2.y >= y) || (p2.y < y && p1.y >= y)) {
                    int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                    nodes.push_back(x);
                }
            }

            std::sort(nodes.begin(), nodes.end());
            for (size_t i = 0; i + 1 < nodes.size(); i += 2) {
                for (int x = nodes[i]; x <= nodes[i + 1]; ++x) {
                    r.setPixel(x, y, color);
                }
            }
        }
    } else {
        LineShape side1(v[0], v[1], color);
        LineShape side2(v[1], v[2], color);
        LineShape side3(v[2], v[0], color);

        side1.draw(r);
        side2.draw(r);
        side3.draw(r);
    }
}