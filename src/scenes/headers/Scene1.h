#pragma once
#include "Scene.h"
#include "LineShape.h"
#include "RectangleShape.h"
#include "CircleShape.h"
#include "TriangleShape.h"
#include "BitmapShape.h"
#include "AnimatedBitmap.h"

/**
 * @brief Przykładowa scena (Scene1) w silniku 2D.
 *
 * Scena zawiera różne figury geometryczne, bitmapy i animacje.
 * Demonstracja możliwości silnika 2D: rysowanie prymitywów, bitmap, animacji i transformacji.
 */
class Scene1 : public Scene {
private:
    /// Linia
    LineShape line;

    /// Prostokąt
    RectangleShape rect;

    /// Koło
    CircleShape circle;

    /// Trójkąt
    TriangleShape triangle;

    /// Statyczna bitmapa
    BitmapShape image;

    /// Animowana bitmapa
    AnimatedBitmap anim;

    /// Timer sceny (np. do animacji lub zakończenia)
    float timer = 0;

public:
    /**
     * @brief Konstruktor sceny.
     *
     * Inicjalizuje wszystkie obiekty sceny oraz ich parametry.
     */
    Scene1();

    /**
     * @brief Aktualizuje logikę sceny.
     *
     * Przesuwa animacje, aktualizuje timer i reaguje na input.
     *
     * @param dt Czas od ostatniej aktualizacji w sekundach
     * @param input Obiekt klasy Input do obsługi klawiatury i myszy
     */
    void update(float dt, const Input& input) override;

    /**
     * @brief Rysuje scenę na ekranie.
     *
     * Wykorzystuje Renderer do rysowania wszystkich figur i bitmap.
     *
     * @param r Obiekt Renderer używany do rysowania
     */
    void draw(Renderer& r) override;

    /**
     * @brief Sprawdza, czy scena zakończyła działanie.
     *
     * @return true jeśli scena powinna się zakończyć, false w przeciwnym wypadku
     */
    bool isFinished() const override;

    /**
     * @brief Zwraca wskaźnik na następną scenę.
     *
     * @return Wskaźnik na kolejną scenę lub nullptr jeśli brak następnej
     */
    Scene* nextScene() const override;
};
