#pragma once

/**
 * @struct Point2D
 * @brief Struktura reprezentująca punkt w przestrzeni 2D.
 *
 * Zawiera współrzędne x i y oraz umożliwia proste operacje arytmetyczne
 * na punktach, takie jak dodawanie i odejmowanie.
 */
struct Point2D {
    float x; ///< Współrzędna X punktu
    float y; ///< Współrzędna Y punktu

    /**
     * @brief Konstruktor inicjalizujący współrzędne punktu.
     *
     * @param x Współrzędna X (domyślnie 0)
     * @param y Współrzędna Y (domyślnie 0)
     */
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}

    /**
     * @brief Operator dodawania dwóch punktów.
     *
     * @param other Punkt, który zostanie dodany do bieżącego
     * @return Nowy punkt będący sumą współrzędnych
     */
    Point2D operator+(const Point2D& other) const {
        return Point2D(x + other.x, y + other.y);
    }

    /**
     * @brief Operator odejmowania dwóch punktów.
     *
     * @param other Punkt, który zostanie odjęty od bieżącego
     * @return Nowy punkt będący różnicą współrzędnych
     */
    Point2D operator-(const Point2D& other) const {
        return Point2D(x - other.x, y - other.y);
    }
};
