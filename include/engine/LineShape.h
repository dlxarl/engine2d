#pragma once
#include "Shape.h"
#include "Point2D.h"

/**
 * @class LineShape
 * @brief Klasa reprezentująca prostą w przestrzeni 2D.
 *
 * Dziedziczy po klasie Shape, umożliwia rysowanie linii
 * między dwoma punktami za pomocą obiektu Renderer.
 */
class LineShape : public Shape {
public:
    Point2D p1; ///< Punkt początkowy linii
    Point2D p2; ///< Punkt końcowy linii

    /**
     * @brief Konstruktor ustawiający punkty linii i jej kolor.
     *
     * @param a Punkt początkowy linii
     * @param b Punkt końcowy linii
     * @param c Kolor linii
     */
    LineShape(Point2D a, Point2D b, Color c);

    /**
     * @brief Rysuje linię w przestrzeni 2D.
     *
     * Implementacja nadpisuje metodę draw() z klasy Shape.
     *
     * @param r Obiekt Renderer odpowiedzialny za rysowanie prymitywów
     */
    void draw(Renderer& r) override;
};
