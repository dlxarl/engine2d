#pragma once
#include "Shape.h"
#include "Point2D.h"
#include <allegro5/allegro.h>
#include <string>

/**
 * @class BitmapShape
 * @brief Klasa reprezentująca statyczną bitmapę rysowaną na ekranie.
 *
 * Umożliwia ładowanie obrazu z pliku oraz rysowanie go w wybranym miejscu.
 * Dziedziczy po klasie Shape, dzięki czemu może być obsługiwana przez Renderer
 * tak samo jak inne prymitywy graficzne.
 */
class BitmapShape : public Shape {
public:
    ALLEGRO_BITMAP* bitmap = nullptr; ///< Załadowana bitmapa (obraz) w formacie Allegro
    Point2D position;                 ///< Pozycja bitmapy w przestrzeni 2D

    /**
     * @brief Konstruktor wczytujący bitmapę z pliku.
     *
     * @param path Ścieżka do pliku graficznego (np. .png, .bmp)
     * @param pos Początkowa pozycja bitmapy
     * @param fallbackColor Kolor zastępczy (fallback), jeśli bitmapa nie mogła zostać wczytana
     */
    BitmapShape(const std::string& path, Point2D pos, Color fallbackColor = Color(255, 0, 255));

    /**
     * @brief Destruktor zwalniający pamięć bitmapy.
     */
    ~BitmapShape();

    /**
     * @brief Rysuje bitmapę w aktualnej pozycji.
     *
     * Implementacja nadpisuje metodę draw() z klasy Shape.
     *
     * @param r Obiekt Renderer odpowiedzialny za rysowanie elementów na ekranie
     */
    void draw(Renderer& r) override;
};
