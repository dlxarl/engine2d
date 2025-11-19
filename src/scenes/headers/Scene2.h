#pragma once
#include "Scene.h"
#include "LineShape.h"
#include "RectangleShape.h"
#include "CircleShape.h"
#include "TriangleShape.h"
#include "BitmapShape.h"
#include "AnimatedBitmap.h"

/**
 * @brief Druga scena (Scene2) w silniku 2D.
 *
 * Scena zawiera różne figury geometryczne i animowaną bitmapę.
 * Demonstruje ruchome obiekty i transformacje w czasie.
 */
class Scene2 : public Scene {
private:
    /// Linia
    LineShape line;

    /// Prostokąt
    RectangleShape rect;

    /// Koło
    CircleShape circle;

    /// Trójkąt
    TriangleShape triangle;

    /// Animowana bitmapa
    AnimatedBitmap anim;

    /// Timer sceny do kontrolowania animacji lub zakończenia
    float timer = 0;

public:
    /**
     * @brief Konstruktor sceny.
     *
     * Inicjalizuje wszystkie obiekty sceny oraz ustawia ich parametry początkowe.
     */
    Scene2();

    /**
     * @brief Aktualizuje logikę sceny.
     *
     * Aktualizuje pozycje figur, timer i reaguje na input użytkownika.
     *
     * @param dt Czas od ostatniej aktualizacji w sekundach
     * @param input Obiekt klasy Input do obsługi klawiatury i myszy
     */
    void update(float dt, const Input& input) override;

    /**
     * @brief Rysuje scenę na ekranie.
     *
     * Rysuje wszystkie figury i animacje przy użyciu Renderera.
     *
     * @param r Obiekt Renderer używany do rysowania
     */
    void draw(Renderer& r) override;

    /**
     * @brief Sprawdza, czy scena zakończyła działanie.
     *
     * @return true jeśli scena powinna zakończyć działanie, false w przeciwnym wypadku
     */
    bool isFinished() const override;

    /**
     * @brief Zwraca wskaźnik na następną scenę.
     *
     * @return Wskaźnik na kolejną scenę lub nullptr jeśli brak następnej
     */
    Scene* nextScene() const override;
};
