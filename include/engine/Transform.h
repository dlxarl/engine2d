#pragma once
#include "Point2D.h"
#include <cmath>

/**
 * @class Transform
 * @brief Klasa odpowiedzialna za przekształcenia geometryczne obiektów 2D.
 *
 * Umożliwia przesuwanie, obracanie oraz skalowanie obiektów w przestrzeni 2D.
 * Może być dziedziczona przez figury, które wymagają transformacji.
 */
class Transform {
public:
    Point2D position;    ///< Pozycja obiektu w przestrzeni 2D
    float rotation = 0;  ///< Kąt obrotu w radianach
    float scaleFactor = 1.0f; ///< Współczynnik skalowania

    /**
     * @brief Konstruktor ustawiający początkową pozycję obiektu.
     *
     * @param pos Pozycja początkowa (domyślnie (0,0))
     */
    Transform(const Point2D& pos = Point2D(0,0)) : position(pos) {}

    /**
     * @brief Przesuwa obiekt o określoną wartość w osi X i Y.
     *
     * @param dx Przesunięcie w osi X
     * @param dy Przesunięcie w osi Y
     */
    void move(float dx, float dy) {
        position.x += dx;
        position.y += dy;
    }

    /**
     * @brief Obraca obiekt o określony kąt.
     *
     * Kąt jest podawany w radianach. Po obrocie kąt jest normalizowany
     * do zakresu [0, 2π].
     *
     * @param deltaAngle Kąt obrotu w radianach
     */
    void rotate(float deltaAngle) {
        rotation += deltaAngle;
        if (rotation > 2*M_PI) rotation -= 2*M_PI;
        if (rotation < 0) rotation += 2*M_PI;
    }

    /**
     * @brief Skalowanie obiektu.
     *
     * Skaluje obiekt przez mnożenie obecnego współczynnika skalowania
     * przez podany faktor. Skalowanie jest ograniczone do zakresu [0.1, 10.0].
     *
     * @param factor Współczynnik skalowania
     */
    void scale(float factor) {
        scaleFactor *= factor;
        if (scaleFactor < 0.1f) scaleFactor = 0.1f;
        if (scaleFactor > 10.0f) scaleFactor = 10.0f;
    }
};
