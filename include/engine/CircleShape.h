#pragma once
#include "Shape.h"
#include "Point2D.h"
#include "Transform.h"

/**
 * @class CircleShape
 * @brief Klasa reprezentująca okrąg lub koło 2D.
 *
 * Obiekt może być rysowany jako obrys lub jako wypełniona figura.
 * Dziedziczy po Shape (rysowanie) oraz Transform (przekształcenia geometryczne).
 */
class CircleShape : public Shape, public Transform {
public:
    Point2D center; ///< Środek okręgu w przestrzeni 2D
    int radius;     ///< Promień okręgu
    bool filled = false; ///< Czy rysować koło (true), czy tylko obrys (false)

    /**
     * @brief Konstruktor ustawiający podstawowe parametry okręgu.
     *
     * @param c Pozycja środka okręgu
     * @param r Promień okręgu
     * @param col Kolor figury
     */
    CircleShape(Point2D c, int r, Color col);

    /**
     * @brief Rysuje okrąg lub koło za pomocą klasy Renderer.
     *
     * @param r Renderer odpowiedzialny za rysowanie prymitywów graficznych
     */
    void draw(Renderer& r) override;

    /**
     * @brief Przełącza tryb wypełnienia.
     *
     * Jeśli figura była obrysem — staje się kołem.
     * Jeśli była kołem — staje się obrysem.
     */
    void toggleFill();
};
