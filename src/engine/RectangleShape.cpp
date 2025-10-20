#include "RectangleShape.h"

RectangleShape::RectangleShape(Point2D p, int w, int h, Color c)
    : Shape(c), pos(p), width(w), height(h) {}

void RectangleShape::draw(Renderer& r) {
    for (int y = pos.y; y < pos.y + height; y++) {
        for (int x = pos.x; x < pos.x + width; x++) {
            r.setPixel(x, y, color);
        }
    }
}
