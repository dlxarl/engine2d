#include "LineShape.h"
#include <cmath>

/**
 * @brief Konstruktor klasy LineShape.
 *
 * Inicjalizuje linię 2D z określonymi punktami końcowymi i kolorem.
 *
 * @param a Punkt początkowy linii
 * @param b Punkt końcowy linii
 * @param c Kolor linii
 */
LineShape::LineShape(Point2D a, Point2D b, Color c) : Shape(c), p1(a), p2(b) {}

/**
 * @brief Rysuje linię 2D przy użyciu algorytmu Bresenhama.
 *
 * Rysuje wszystkie piksele od punktu p1 do punktu p2, używając koloru
 * zdefiniowanego w obiekcie Shape::color.
 *
 * @param r Obiekt Renderer używany do rysowania pikseli
 */
void LineShape::draw(Renderer& r){
    int x1 = (int)p1.x, y1 = (int)p1.y;
    int x2 = (int)p2.x, y2 = (int)p2.y;
    int dx = abs(x2-x1), dy = abs(y2-y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(true){
        r.setPixel(x1, y1, color);
        if( x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if(e2 > -dy) {err -= dy; x1 += sx; }
        if(e2 < dx) {err += dx; y1 += sy; }
    }
}
