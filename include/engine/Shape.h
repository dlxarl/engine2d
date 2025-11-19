#pragma once
#include "Color.h"
#include "Renderer.h"

/**
 * @class Shape
 * @brief Klasa bazowa dla wszystkich prymitywów graficznych w silniku 2D.
 *
 * Udostępnia wspólny interfejs do rysowania obiektów za pomocą renderera.
 * Wszystkie klasy dziedziczące muszą zaimplementować metodę draw().
 */
class Shape {
public:
    Color color; ///< Kolor figury

    /**
     * @brief Konstruktor ustawiający kolor figury.
     *
     * @param c Kolor przypisany do obiektu
     */
    Shape(Color c) : color(c) {}

    /**
     * @brief Wirtualny destruktor klasy bazowej.
     */
    virtual ~Shape() = default;

    /**
     * @brief Czysto wirtualna metoda rysująca obiekt.
     *
     * Każda klasa dziedzicząca musi zaimplementować tę metodę.
     *
     * @param renderer Obiekt Renderer używany do rysowania
     */
    virtual void draw(Renderer& renderer) = 0;
};
