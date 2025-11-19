#include "RectangleShape.h"
#include <cmath>
#include <algorithm>

RectangleShape::RectangleShape(Point2D p, int w, int h, Color border)
    : Shape(border), Transform(p), width(w), height(h), borderColor(border), fillColor(border)
{

}

void RectangleShape::draw(Renderer& r) {

    float cx = position.x;
    float cy = position.y;


    float hw = width * 0.5f * scaleFactor;
    float hh = height * 0.5f * scaleFactor;


    Point2D corners[4] = {
        {-hw, -hh},
        { hw, -hh},
        { hw,  hh},
        {-hw,  hh}
    };


    float cosR = std::cos(rotation);
    float sinR = std::sin(rotation);

    for (int i = 0; i < 4; ++i) {
        float x = corners[i].x;
        float y = corners[i].y;


        float xr = x * cosR - y * sinR;
        float yr = x * sinR + y * cosR;


        corners[i].x = xr + cx;
        corners[i].y = yr + cy;
    }


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


    if (filled) {
        float cosNegR = std::cos(-rotation);
        float sinNegR = std::sin(-rotation);


        int minX = static_cast<int>(std::min({corners[0].x, corners[1].x, corners[2].x, corners[3].x}));
        int maxX = static_cast<int>(std::max({corners[0].x, corners[1].x, corners[2].x, corners[3].x}));
        int minY = static_cast<int>(std::min({corners[0].y, corners[1].y, corners[2].y, corners[3].y}));
        int maxY = static_cast<int>(std::max({corners[0].y, corners[1].y, corners[2].y, corners[3].y}));

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {

                float lx = (x - cx) * cosNegR - (y - cy) * sinNegR;
                float ly = (x - cx) * sinNegR + (y - cy) * cosNegR;

                if (lx >= -hw && lx <= hw && ly >= -hh && ly <= hh) {
                    r.setPixel(x, y, fillColor);
                }
            }
        }
    }
}

void RectangleShape::toggleFill() {
    filled = !filled;
}