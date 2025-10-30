#include "RectangleShape.h"

RectangleShape::RectangleShape(Point2D p, int w, int h, Color fill, Color border)
    : Shape(fill), pos(p), width(w), height(h), fillColor(fill), borderColor(border) {}

void RectangleShape::draw(Renderer& r) {
    // Рамка
    for (int x = pos.x; x < pos.x + width; x++) {
        r.setPixel(x, pos.y, borderColor);
        r.setPixel(x, pos.y + height - 1, borderColor);
    }
    for (int y = pos.y; y < pos.y + height; y++) {
        r.setPixel(pos.x, y, borderColor);
        r.setPixel(pos.x + width - 1, y, borderColor);
    }

    // Заповнення
    for (int y = pos.y + 1; y < pos.y + height - 1; y++) {
        for (int x = pos.x + 1; x < pos.x + width - 1; x++) {
            r.setPixel(x, y, fillColor);
        }
    }
}