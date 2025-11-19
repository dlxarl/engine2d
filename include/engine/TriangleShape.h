#pragma once
#include "Shape.h"
#include "Transform.h"
#include "Point2D.h"

/**
 * @class TriangleShape
 * @brief Klasa reprezentująca trójkąt 2D.
 *
 * Trójkąt może być rysowany jako obrys lub wypełniona figura.
 * Dziedziczy po Shape (rysowanie) oraz Transform (przekształcenia geometryczne).
 */
class TriangleShape : public Shape, public Transform {
public:
    float size;   ///< Rozmiar trójkąta (długość boku)
    float hue = 0.0f; ///< Barwa (odcień) trójkąta
    bool filled = false; ///< Czy trójkąt jest wypełniony (true) czy tylko obrys (false)

    /**
     * @brief Konstruktor ustawiający podstawowe parametry trójkąta.
     *
     * @param pos Pozycja trójkąta w przestrzeni 2D
     * @param s Rozmiar trójkąta
     * @param col Kolor trójkąta
     */
    TriangleShape(Point2D pos, float s, Color col);

    /**
     * @brief Rysuje trójkąt w przestrzeni 2D.
     *
     * Implementacja nadpisuje metodę draw() z klasy Shape.
     *
     * @param r Obiekt Renderer odpowiedzialny za rysowanie prymitywów
     */
    void draw(Renderer& r) override;

    /**
     * @brief Przełącza tryb wypełnienia trójkąta.
     *
     * Jeśli figura była obrysem — staje się wypełniona.
     * Jeśli była wypełniona — staje się obrysem.
     */
    void toggleFill();
};
