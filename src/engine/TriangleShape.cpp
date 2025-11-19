#include "TriangleShape.h"
#include "LineShape.h"
#include <cmath>
#include <algorithm>
#include <vector>

TriangleShape::TriangleShape(Point2D c, float s, Color col)
    : Shape(col), Transform(c), size(s) {}

void TriangleShape::toggleFill() {
    filled = !filled;
}

void TriangleShape::draw(Renderer& r) {
    Point2D v[3];

    // Рахуємо вершини трикутника з урахуванням rotation та position
    for (int i = 0; i < 3; ++i) {
        float a = rotation + i * 2.0f * M_PI / 3.0f; // rotation з Transform
        float dx = std::cos(a) * size * scaleFactor;
        float dy = std::sin(a) * size * scaleFactor;

        v[i] = Point2D(
            position.x + dx,
            position.y + dy
        );
    }

    if (filled) {
        // Triangle fill (scanline)
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
        // Outline
        LineShape side1(v[0], v[1], color);
        LineShape side2(v[1], v[2], color);
        LineShape side3(v[2], v[0], color);

        side1.draw(r);
        side2.draw(r);
        side3.draw(r);
    }
}
