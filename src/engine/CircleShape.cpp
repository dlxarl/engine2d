#include "CircleShape.h"

CircleShape::CircleShape(Point2D c, int r, Color col) : Shape(col), center(c), radius(r) {}

void CircleShape::toggleFill() {
    filled = !filled;
}


void CircleShape::draw(Renderer& r) {
    if (filled) {
        // Заповнення кола
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x*x + y*y <= radius*radius) {
                    r.setPixel(center.x + x, center.y + y, color);
                }
            }
        }
    } else {
        // Контур кола (алгоритм Брезенхема)
        int x = 0, y = radius;
        int d = 1 - radius;

        auto drawCirclePoints = [&](int cx, int cy, int x, int y) {
            r.setPixel(cx + x, cy + y, color);
            r.setPixel(cx - x, cy + y, color);
            r.setPixel(cx + x, cy - y, color);
            r.setPixel(cx - x, cy - y, color);
            r.setPixel(cx + y, cy + x, color);
            r.setPixel(cx - y, cy + x, color);
            r.setPixel(cx + y, cy - x, color);
            r.setPixel(cx - y, cy - x, color);
        };

        while (y >= x) {
            drawCirclePoints(center.x, center.y, x, y);
            if (d < 0)
                d += 2 * x + 3;
            else {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
        }
    }
}
