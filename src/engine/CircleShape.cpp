#include "CircleShape.h"
#include <cmath>

CircleShape::CircleShape(Point2D c, int r, Color col)
    : Shape(col), Transform(c), radius(r)
{
}

void CircleShape::toggleFill() {
    filled = !filled;
}

void CircleShape::draw(Renderer& r) {
    int scaledRadius = static_cast<int>(radius * scaleFactor);

    int cx = static_cast<int>(position.x); // беремо position з Transform
    int cy = static_cast<int>(position.y);

    if (filled) {
        for (int y = -scaledRadius; y <= scaledRadius; y++) {
            for (int x = -scaledRadius; x <= scaledRadius; x++) {
                if (x*x + y*y <= scaledRadius*scaledRadius) {
                    r.setPixel(cx + x, cy + y, color);
                }
            }
        }
    } else {
        int x = 0;
        int y = scaledRadius;
        int d = 1 - scaledRadius;

        auto drawCirclePoints = [&](int px, int py, int x, int y) {
            r.setPixel(px + x, py + y, color);
            r.setPixel(px - x, py + y, color);
            r.setPixel(px + x, py - y, color);
            r.setPixel(px - x, py - y, color);
            r.setPixel(px + y, py + x, color);
            r.setPixel(px - y, py + x, color);
            r.setPixel(px + y, py - x, color);
            r.setPixel(px - y, py - x, color);
        };

        while (y >= x) {
            drawCirclePoints(cx, cy, x, y);
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
