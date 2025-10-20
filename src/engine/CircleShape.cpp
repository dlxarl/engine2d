#include "CircleShape.h"

CircleShape::CircleShape(Point2D c, int r, Color col) : Shape(col), center(c), radius(r) {}

void CircleShape::draw(Renderer& r) {
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
