#include "CircleShape.h"
#include <cmath>

/**
 * @brief Konstruktor klasy CircleShape.
 *
 * Inicjalizuje okrąg o określonym środku, promieniu i kolorze.
 *
 * @param c Środek okręgu w przestrzeni 2D
 * @param r Promień okręgu
 * @param col Kolor okręgu
 */
CircleShape::CircleShape(Point2D c, int r, Color col)
    : Shape(col), Transform(c), radius(r)
{
}

/**
 * @brief Przełącza tryb wypełnienia okręgu.
 *
 * Jeśli figura była obrysem — staje się wypełniona.
 * Jeśli była wypełniona — staje się obrysem.
 */
void CircleShape::toggleFill() {
    filled = !filled;
}

/**
 * @brief Rysuje okrąg w przestrzeni 2D.
 *
 * W zależności od trybu rysuje wypełniony okrąg lub sam obrys.
 * Uwzględnia skalowanie obiektu (scaleFactor z klasy Transform).
 *
 * @param r Obiekt Renderer używany do rysowania pikseli
 */
void CircleShape::draw(Renderer& r) {
    int scaledRadius = static_cast<int>(radius * scaleFactor);

    int cx = static_cast<int>(position.x);
    int cy = static_cast<int>(position.y);

    if (filled) {
        // Rysowanie wypełnionego okręgu
        for (int y = -scaledRadius; y <= scaledRadius; y++) {
            for (int x = -scaledRadius; x <= scaledRadius; x++) {
                if (x*x + y*y <= scaledRadius*scaledRadius) {
                    r.setPixel(cx + x, cy + y, color);
                }
            }
        }
    } else {
        // Rysowanie obrysu okręgu metodą Bresenhama
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
