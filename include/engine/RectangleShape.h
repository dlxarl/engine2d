#pragma once
#include "Shape.h"
#include "Renderer.h"
#include "Point2D.h"
#include "Color.h"
#include "Transform.h"

/**
 * @class RectangleShape
 * @brief Klasa reprezentująca prostokąt 2D.
 *
 * Prostokąt może być rysowany jako obrys lub wypełniona figura.
 * Dziedziczy po Shape (rysowanie) oraz Transform (przekształcenia geometryczne).
 */
class RectangleShape : public Shape, public Transform {
public:
    Point2D pos;     ///< Pozycja lewego górnego rogu prostokąta
    int width;       ///< Szerokość prostokąta
    int height;      ///< Wysokość prostokąta

    Color fillColor;   ///< Kolor wypełnienia prostokąta
    Color borderColor; ///< Kolor obrysu prostokąta

    bool filled = false; ///< Czy prostokąt jest wypełniony (true) czy tylko obrys (false)

    /**
     * @brief Konstruktor ustawiający podstawowe parametry prostokąta.
     *
     * @param p Pozycja lewego górnego rogu
     * @param w Szerokość prostokąta
     * @param h Wysokość prostokąta
     * @param border Kolor obrysu prostokąta
     */
    RectangleShape(Point2D p, int w, int h, Color border);

    /**
     * @brief Przełącza tryb wypełnienia prostokąta.
     *
     * Jeśli figura była obrysem — staje się wypełniona.
     * Jeśli była wypełniona — staje się obrysem.
     */
    void toggleFill();

    /**
     * @brief Rysuje prostokąt w przestrzeni 2D.
     *
     * Implementacja nadpisuje metodę draw() z klasy Shape.
     *
     * @param r Obiekt Renderer odpowiedzialny za rysowanie prymitywów
     */
    void draw(Renderer& r) override;
};
