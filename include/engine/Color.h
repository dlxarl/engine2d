#pragma once
#include <cstdint>

/**
 * @struct Color
 * @brief Struktura reprezentująca kolor w formacie RGB.
 *
 * Zawiera trzy składowe koloru: czerwony (r), zielony (g) i niebieski (b).
 * Domyślnie każda składowa ustawiona jest na 0 (czarny kolor).
 */
struct Color {
    uint8_t r; ///< Składowa koloru czerwonego (0–255)
    uint8_t g; ///< Składowa koloru zielonego (0–255)
    uint8_t b; ///< Składowa koloru niebieskiego (0–255)

    /**
     * @brief Konstruktor inicjalizujący kolor.
     *
     * @param r Wartość czerwonego (0–255), domyślnie 0
     * @param g Wartość zielonego (0–255), domyślnie 0
     * @param b Wartość niebieskiego (0–255), domyślnie 0
     */
    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {}
};
