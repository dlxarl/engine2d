#include "RectangleShape.h"
#include <cmath>
#include <algorithm>

RectangleShape::RectangleShape(Point2D p, int w, int h, Color border)
    : Shape(border), Transform(p), width(w), height(h), borderColor(border), fillColor(border)
{
    // fillColor за замовчуванням такий самий, як borderColor
}

void RectangleShape::draw(Renderer& r) {
    // Центр прямокутника
    float cx = position.x;
    float cy = position.y;

    // Півширина і піввисота з урахуванням масштабу
    float hw = width * 0.5f * scaleFactor;
    float hh = height * 0.5f * scaleFactor;

    // Кути прямокутника відносно центру
    Point2D corners[4] = {
        {-hw, -hh},
        { hw, -hh},
        { hw,  hh},
        {-hw,  hh}
    };

    // Обертання кутів
    float cosR = std::cos(rotation);
    float sinR = std::sin(rotation);

    for (int i = 0; i < 4; ++i) {
        float x = corners[i].x;
        float y = corners[i].y;

        // Поворот навколо центру
        float xr = x * cosR - y * sinR;
        float yr = x * sinR + y * cosR;

        // Зсув до позиції
        corners[i].x = xr + cx;
        corners[i].y = yr + cy;
    }

    // Малюємо контур (з'єднуємо кути)
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        int x0 = static_cast<int>(corners[i].x);
        int y0 = static_cast<int>(corners[i].y);
        int x1 = static_cast<int>(corners[next].x);
        int y1 = static_cast<int>(corners[next].y);

        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            r.setPixel(x0, y0, borderColor);
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 < dx)  { err += dx; y0 += sy; }
        }
    }

    // Малювання заповнення
    if (filled) {
        // Визначаємо bounding box
        int minX = static_cast<int>(std::min({corners[0].x, corners[1].x, corners[2].x, corners[3].x}));
        int maxX = static_cast<int>(std::max({corners[0].x, corners[1].x, corners[2].x, corners[3].x}));
        int minY = static_cast<int>(std::min({corners[0].y, corners[1].y, corners[2].y, corners[3].y}));
        int maxY = static_cast<int>(std::max({corners[0].y, corners[1].y, corners[2].y, corners[3].y}));

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                r.setPixel(x, y, fillColor);
            }
        }
    }
}

void RectangleShape::toggleFill() {
    filled = !filled;
}